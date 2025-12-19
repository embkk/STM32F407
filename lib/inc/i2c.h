#ifndef I2C_H
#define I2C_H

#include <stdint.h>

#define I2C_DEV_ADDR        0XA0
#define I2C_WR_BIT          0X00
#define I2C_RD_BIT          0X01
#define I2C_DEV_ADDR_RD     (I2C_DEV_ADDR + I2C_RD_BIT)
#define I2C_DEV_ADDR_WR     (I2C_DEV_ADDR + I2C_WR_BIT)

#define EEPROM_REGION_ADDR  0x08
#define EEPROM_PAGE_LEN       8

extern unsigned char eeprom_addr;
extern unsigned char eeprom_addr_offset;

void I2C_Write(char, char*, uint16_t);
void I2C_Read(char, char*, uint16_t);
void I2C_init(void);

#endif