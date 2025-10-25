#include "i2c.h"
#include "log.h"
#include "stm32f407xx.h"
#include "tools.h"

unsigned char eeprom_addr = EEPROM_REGION_ADDR;
unsigned char eeprom_addr_offset = 0;

void I2C_TX_device_addr(char device_address, char RW_bit) {
  I2C1 -> DR = (device_address + RW_bit);
  //I2C1->DR = (device_address << 1) | RW_bit;
  while((I2C1->SR1 & I2C_SR1_ADDR)==0) {}
  (void)I2C1->SR1;
  (void)I2C1->SR2;
}

void I2C_start_gen(void) {
  I2C1->CR1 |= I2C_CR1_START;
  wait_while((I2C1->SR1 & I2C_SR1_SB) == 0);
}

void I2C_stop_gen(void) {
  I2C1->CR1 |= I2C_CR1_STOP;
}

void I2C_Read(char start_addr, char* data, uint16_t data_len) {
  LOG_MESSAGE("Read eeprom [%d] from %x", data_len, start_addr);
  // ACK turn on
  I2C1->CR1 |= I2C_CR1_ACK;

  // gen Start-condition
  I2C_start_gen();

  // send addr to I2C
  I2C_TX_device_addr(I2C_DEV_ADDR, I2C_WR_BIT);

  I2C1 ->DR = start_addr;
  wait_while((I2C1->SR1 & I2C_SR1_TXE) == 0);

  // gen Start condition again
  I2C_start_gen();

  I2C_TX_device_addr(I2C_DEV_ADDR, I2C_RD_BIT);

  // read data (w/o last byte)
  for(uint16_t i =0;  i<data_len-1; i++) {
    wait_while((I2C1->SR1 & I2C_SR1_RXNE)==0);
    data[i]=I2C1->DR;
    LOG_MESSAGE("Read %d", data[i]);
  }

  //stop acknowlege
  I2C1->CR1 &= ~(I2C_CR1_ACK);

  // last byte
  wait_while((I2C1->SR1 & I2C_SR1_RXNE)==0);
  data[data_len-1] = I2C1->DR;

  // gen Stop-condition
  I2C_stop_gen();
}

void I2C_Write(char start_addr, char* data, uint16_t data_len) {
  LOG_MESSAGE("Write eeprom [%d] to %x", data_len, start_addr);
  // ACK turn on
  I2C1->CR1 |= I2C_CR1_ACK;

  // check I2C free
  wait_while((I2C1-> SR2 & I2C_SR2_BUSY)!=0);

  // gen Start-condition
  I2C_start_gen();

  // send addr to I2C
  I2C_TX_device_addr(I2C_DEV_ADDR, I2C_WR_BIT);

  I2C1 ->DR = start_addr;
  wait_while((I2C1->SR1 & I2C_SR1_TXE) == 0);

  // send data
  for(uint16_t i =0;  i<data_len; i++) {
    I2C1->DR = data[i];
    LOG_MESSAGE("Write %d", data[i]);
    wait_while((I2C1->SR1 & I2C_SR1_TXE) == 0);
  }

  // gen Stop-condition
  I2C_stop_gen();
}

void I2C_init(void) {
  RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
  RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOBEN; //E,A,B

  GPIOB -> MODER |= GPIO_MODER_MODE8_1 | GPIO_MODER_MODE9_1;
  GPIOB->OTYPER |= (GPIO_OTYPER_OT8 | GPIO_OTYPER_OT9);

  GPIOB->AFR[1] |= GPIO_AFRH_AFRH0_2   | GPIO_AFRH_AFRH1_2;
  //GPIOB->AFR[1] |= (4<<GPIO_AFRH_AFSEL8_Pos) | (4<<GPIO_AFRH_AFSEL9_Pos);

  I2C1->CR2 |=  (42 << I2C_CR2_FREQ_Pos);
  

  // I2C = 100 KHz
  // Tlow = Thigh = CCR * T_plck1
  // Tsm = 1/(I2C_freq) = Thigh + Tlow;
  // 1/100k = 2 * CCR * T_plck1
  // T_plck1 = 1 / Freq_APB1 = 1 / 42MHz
  // CCR = 1 / 200k / T_plck1 = 42MHz / 200k
  // CCR = 210

  I2C1->CCR = 0;
  I2C1->CCR |= (210 << I2C_CCR_CCR_Pos);
  I2C1->CCR &= ~I2C_CCR_FS;

  I2C1->TRISE |= (43 << I2C_TRISE_TRISE_Pos); // TRISE = FREQ+1
  I2C1->OAR1 &= ~(I2C_OAR1_ADDMODE);          // 7bit address

  I2C1->CR1 |= I2C_CR1_PE;                    //I2C1 enabled
  I2C1->CR1 |= I2C_CR1_ACK;                   //acknowlege enabled

}