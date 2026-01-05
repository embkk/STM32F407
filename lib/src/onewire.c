#include "onewire.h"
#include <stdio.h>
#include "stm32f407xx.h"
#include "delay.h"



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



// crc
#define CRC_POLYNOM       (uint8_t)0x31
#define CRC_LEN_8_BITS    8

// 1wire
#define ROM64_BYTE_LEN    8
#define ROM64_BIT_LEN     64
#define BYTE_LEN          8
#define SCRATCH_BYTE_LEN  9

uint8_t Start_1wire(void) {
  tx_mode_1wire();
  pull_low_1wire(); //master reset
  Delay_us(500);
  release_1wire();
  rx_mode_1wire();
  Delay_us(100); // wait 100 us = 60 us pause + 40 us presense pulse
  
  uint8_t state = check_1wire();
  //printf("1wire line state: %d\n", state);  // должно быть 0

  if(state) {
    return 1; // no presence pulse from 1wire device
  } else {
    Delay_us(200);
    return 0; // received presence pulse from 1wire
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
