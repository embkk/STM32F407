#ifndef SPI_H
#define SPI_H


#include "gpio.h"
#include "tools.h"

uint8_t w25send(uint8_t);
uint16_t w25send_16bit(uint16_t);
void SPI2_Init(uint32_t);

#define EN_RST  0x66
#define RST     0x99
#define WR_EN   0x06
#define SECT_ER 0x20
#define RD_SR1  0x05
#define PG_PROG 0x02
#define RD_DATA 0x03

#define w25_open(expr) GPIO_pin_reset(E, 3); \
expr; \
GPIO_pin_set(E, 3)


#define w25send_addr(addr) LOG_MESSAGE("w25 send addr %p", addr); \
w25send((addr>>16) & 0xFF); \
w25send((addr>>8) & 0xFF); \
w25send((addr) & 0xFF);

#endif