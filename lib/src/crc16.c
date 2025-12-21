#include "crc16.h"

uint16_t CRC16_calc(uint8_t mass[], uint8_t mass_len) {
  uint16_t crc16_reg = 0xFFFF;
  for(uint8_t i =0; i< mass_len; i++ ) {
    crc16_reg = crc16_reg ^ ( mass[i] & 0x00FF );
    for(uint8_t j=0; j<BYTE_LEN; j++) {
      if(crc16_reg & 0x0001) {
        crc16_reg = crc16_reg >> 1;
        crc16_reg = crc16_reg & POLY_16;
      } else {
        crc16_reg = crc16_reg >> 1;
      }
    }
  }
  return crc16_reg;
}