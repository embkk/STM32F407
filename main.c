#include "stm32f4xx.h"
#include <stdlib.h>
#include <stdio.h>
#include "log.h"
#include "usart.h"
 
void RCC_Init(void);

#define SENSOR_CHECK_TIME_US  3000

// 1wire PE2
#define release_1wire()     (GPIOE->BSRR  |= GPIO_BSRR_BS2)
#define pull_low_1wire()    (GPIOE->BSRR  |= GPIO_BSRR_BR2)
#define rx_mode_1wire()     (GPIOE->MODER &= ~GPIO_MODER_MODE2_0)
#define tx_mode_1wire()     (GPIOE->MODER |= GPIO_MODER_MODE2_0)
#define check_1wire()       ((GPIOE->IDR & GPIO_IDR_ID2) != 0)

// 1wire ROM
#define READ_ROM      0x33
#define MATCH_ROM     0x55
#define SKIP_ROM      0xCC
#define SEARCH_ROM    0xF0
#define ALARM_SEARCH  0xEC

// 1wire memory command
#define READ_SCRATCH  0xBE
#define WRITE_SCRATCH 0x4E
#define COPY_SCRATCH  0x48
#define CONVERT_T     0x44
#define RECALL_E2     0xB8
#define READ_PWR      0xB4

// 1wire error codes
#define  OK_1WIRE         0
#define  NO_DEVICE_1WIRE  1
#define  CRC_ERR_1WIRE     1

// crc
#define CRC_POLYNOM       (uint8_t)0x31
#define CRC_LEN_8_BITS    8

// 1wire
#define ROM64_BYTE_LEN    8
#define ROM64_BIT_LEN     64
#define BYTE_LEN          8
#define SCRATCH_BYTE_LEN  9

uint32_t us_count = 0;
uint32_t delay_us_count = 0;

void GPIO_Init() {
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
  
  GPIOE->PUPDR |= GPIO_PUPDR_PUPD10_0;
  GPIOE->PUPDR |= GPIO_PUPDR_PUPD11_0;
  GPIOE->PUPDR |= GPIO_PUPDR_PUPD12_0;

  GPIOE->MODER |= GPIO_MODER_MODE13_0;
  GPIOE->MODER |= GPIO_MODER_MODE14_0;
  GPIOE->MODER |= GPIO_MODER_MODE15_0;

  //1wire pe2 pin
  GPIOE->MODER  |= GPIO_MODER_MODE2_0; //PE2 Output
  GPIOE->OTYPER |= GPIO_OTYPER_OT2;    //PE2 Open Drain
}

int t = 0;
int __SEGGER_RTL_X_file_write(__SEGGER_RTL_FILE *__stream, const char *__s, unsigned __len) {
  t++;
  LOG_MESSAGE("%0d %0ds: [%s]", t, __len, __s);
  return 0;
  for(; __len!=0; --__len) {
    USART1->DR = * __s++;
    while(RESET == READ_BIT(USART1->SR, USART_SR_TXE));
  }

  return 0;
}

void Delay_us(uint32_t us_number) {
  delay_us_count = 0;
  while(delay_us_count< us_number) {};
}

uint8_t Start_1wire(void) {
  tx_mode_1wire();
  pull_low_1wire(); //master reset
  Delay_us(500);
  release_1wire();
  rx_mode_1wire();
  Delay_us(100);    // wait 100 us = 60 us pause + 40 us presense pulse
  
  uint8_t state = check_1wire();
  printf("1wire line state: %d\n", state);  // должно быть 0

  if(state) {
    return 1;       // no presence pulse from 1wire device
  } else {
    Delay_us(200);
    return 0;       // received presence pulse from 1wire
  }
}

void WriteByte_1wire(uint8_t byte_value) {
  uint8_t write_bit_code = 0;
  uint8_t tmp = 0;
  tx_mode_1wire();
  for(uint8_t i=0; i<8; i++) {
    write_bit_code = 0;
    tmp = (1<<i);
    write_bit_code = (byte_value & tmp);
    pull_low_1wire();
    Delay_us(5);
    if(write_bit_code != 0) {
      release_1wire();
    }
    Delay_us(55);
    release_1wire();
    Delay_us(2);
  }
}

uint8_t ReadByte_1wire(void) {
  uint8_t rx_byte = 0;
  for(uint8_t i=0; i<8; i++) {
    tx_mode_1wire();
    pull_low_1wire();
    Delay_us(2);
    release_1wire(); 
    rx_mode_1wire();
    Delay_us(12);
    if(check_1wire()) { // if received
      rx_byte |= (1 << i);
    }
    Delay_us(60-12-2); // read bit slot time = 60 us
    tx_mode_1wire();
    release_1wire();
    Delay_us(2);
  }
  return rx_byte;
}

uint8_t CRC_Calc(uint8_t mass[], uint8_t mass_size, uint8_t POLY) {
  uint8_t crc = 0, crc_out = 0;
  uint8_t in_data;
  uint8_t in_bits;
  for(uint8_t j=0; j < mass_size; j++) {
    in_data = mass[j];
    for(uint8_t i = 0; i <8; i++) {
      if(((crc & 0x80) >> 7) != (in_data & 0x01)) {
        crc = crc << 1;
        crc = crc ^ POLY;
      } else {  
        crc = crc << 1;
      }
      in_data = in_data >> 1;
    }
  }
  //разворот
  for(uint8_t i=0; i<8; i++) {
    if(crc & (1 << i)) crc_out |= (1<<(7-i));
  }
  return crc_out;
}

uint8_t Read_ROM64(uint8_t *family_code, uint8_t ser_num[], uint8_t *crc) {
  uint8_t tmp_array[ROM64_BYTE_LEN];
  uint8_t crc_calculated = 0;
  uint8_t err_code = 0;
  if(!Start_1wire()) {
    WriteByte_1wire(READ_ROM);
    Delay_us(100);
    *family_code = ReadByte_1wire();
    tmp_array[0] = *family_code;
    for(uint8_t i =0; i<6; i++) {
      ser_num[i] = ReadByte_1wire();
      tmp_array[i+1] = ser_num[i];
    }
    *crc = ReadByte_1wire();
    tmp_array[7] = *crc;
    printf("============== \n");
    printf("==== READ ROM 64 bits\n==== SCRATCH =");
    for(uint8_t i =0 ; i< ROM64_BYTE_LEN; i++) {
      printf("0x%X ", tmp_array[i]);
    }
    printf("\n==== CRC Rx = 0x%X \n", tmp_array[7]);

    crc_calculated = CRC_Calc(tmp_array, 7, CRC_POLYNOM);
    printf("==== CRC calculated = 0x%X \n", crc_calculated);

    if(crc_calculated == tmp_array[7]) {
      return OK_1WIRE;
    } else {
      return CRC_ERR_1WIRE;
    }
  } else {
    return NO_DEVICE_1WIRE;
  }
}

uint8_t ReadScratchpad(uint8_t scratch_array[]) {
  uint8_t err_code = 0;
  uint16_t temp = 0;
  uint8_t scratch_tmp[ROM64_BYTE_LEN] = {};
  uint8_t crc_calculated = 0;
  if(!Start_1wire()) {
    WriteByte_1wire(SKIP_ROM);
    Delay_us(100);
    WriteByte_1wire(READ_SCRATCH);
    Delay_us(100);
    for(uint8_t i=0; i<SCRATCH_BYTE_LEN;i++) {
      scratch_tmp[i] = ReadByte_1wire();
      Delay_us(100);
    }

    crc_calculated = CRC_Calc(scratch_tmp, SCRATCH_BYTE_LEN-1, CRC_POLYNOM);
    if(crc_calculated == scratch_tmp[SCRATCH_BYTE_LEN-1]) {
      for(uint8_t i = 0; i<SCRATCH_BYTE_LEN; i++) {
        scratch_array[i] = scratch_tmp[i];
      }
      return OK_1WIRE;
    } else {
      printf("--- Error Scratch CRC mismatch");
      return CRC_ERR_1WIRE;
    }
  } else {
    return NO_DEVICE_1WIRE;
  }
}

uint8_t WriteScratch(uint8_t tx_array[]) {
  if(!Start_1wire()) {
    WriteByte_1wire(SKIP_ROM);
    Delay_us(100);
    WriteByte_1wire(WRITE_SCRATCH);
    Delay_us(100);
    for(uint8_t i=0; i<3;i++) {
      WriteByte_1wire(tx_array[i]);
      Delay_us(100);
    }
    Start_1wire();
    return OK_1WIRE;
  }
  return NO_DEVICE_1WIRE;
}

uint8_t Convert_Temperature(void) {
  uint8_t err_code = 0;
  uint16_t temp = 0;
  if(!Start_1wire()) {
    WriteByte_1wire(SKIP_ROM);
    Delay_us(100);
    WriteByte_1wire(CONVERT_T);
    Delay_us(100);
    return OK_1WIRE;
  } else {
    return NO_DEVICE_1WIRE;
  }
}

void SysTick_Handler(void)
{
  delay_us_count++;
  us_count++;
}

uint8_t error_1wire = 0;
uint8_t family_byte = 0;
uint8_t ser_number[6] = {};
uint8_t crc_rx = 0;
uint8_t scratch_mem[9] = {};
uint16_t temper;
uint16_t temper_fract;
float temper_float;

int main(void) {
  
  LOG_INIT();

  SystemInit();
  SysTick_Config(84000);
  
  RCC_Init();
  USART_init();
  GPIO_Init();

  GPIOE->BSRR |=  GPIO_BSRR_BS13;
  GPIOE->BSRR |=  GPIO_BSRR_BS14;
  GPIOE->BSRR |=  GPIO_BSRR_BS15;

  LOG_MESSAGE("Init complete");
  release_1wire();
  
  while(1) {
    error_1wire = Read_ROM64(&family_byte, ser_number, &crc_rx);
    if( error_1wire == OK_1WIRE ) {
      printf("+++ DS18B20 found +++ \n");
      printf("+++ FAMILY CODE = %X \n", family_byte);
      printf("+++ SERIAL NUMBER = ");

      for(uint8_t i =0; i<6; i++ ) {
        printf("%X ", ser_number[i]);
      }
      printf("\n");
    } else {
      printf("---- ERROR: 1-Wire DS18B20 not found \n");
    }
    
    //config
    scratch_mem[0] = 0x64;  //TH = 100
    scratch_mem[1] = 0x0A;  // TL = 10
    scratch_mem[2] = 0x1F;  // 9bit

    Convert_Temperature();

    while(us_count < SENSOR_CHECK_TIME_US) {};
    us_count = 0;

    error_1wire = ReadScratchpad(scratch_mem);
    if(error_1wire == OK_1WIRE) {
      temper = ((scratch_mem[1] << 8 )) + scratch_mem[0];

      if(temper < 0x0800) {
        temper_fract = ((temper & 0x000F)*100) >> 4;
        temper_float = (float)temper / 16;
        printf(" = %d.%02d \t", (temper >> 4), temper_fract);

        temper_float = (float)temper/16;
      } else {
        temper = (0xFFFF - temper) + 1;
        temper_fract = (((temper & 0x000F)*100)>>4);
        printf("= -%d.%02d \t", (temper>>4), temper_fract);

        temper_float = (float)temper/16;
        printf("(float) = -%f \n", temper_float);
      }
    }

  }//while(1)
}
