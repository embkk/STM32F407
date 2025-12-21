#ifndef CRC16_H
#define CRC16_H

#include <stdint.h>

#define BYTE_LEN  8
#define POLY_16   0xA001
uint16_t CRC16_calc(uint8_t[], uint8_t);

#endif