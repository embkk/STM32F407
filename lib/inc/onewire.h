#ifndef ONEWIRE_H
#define ONEWIRE_H

#include <stdint.h>

// 1wire error codes
#define  OK_1WIRE         0
#define  NO_DEVICE_1WIRE  1
#define  CRC_ERR_1WIRE     1

// 1wire PE2
#define release_1wire()     (GPIOE->BSRR  |= GPIO_BSRR_BS2)
#define pull_low_1wire()    (GPIOE->BSRR  |= GPIO_BSRR_BR2)
#define rx_mode_1wire()     (GPIOE->MODER &= ~GPIO_MODER_MODE2_Msk)
#define tx_mode_1wire()     (GPIOE->MODER |= GPIO_MODER_MODE2_0)
#define check_1wire()       ((GPIOE->IDR & GPIO_IDR_ID2) != 0)

uint8_t Start_1wire(void);

void WriteByte_1wire(uint8_t);

uint8_t ReadByte_1wire(void);

uint8_t CRC_Calc(uint8_t[], uint8_t, uint8_t);


uint8_t Read_ROM64(uint8_t*, uint8_t [], uint8_t *);

uint8_t ReadScratchpad(uint8_t []);

uint8_t WriteScratch(uint8_t[]);

uint8_t Convert_Temperature(void);

#endif