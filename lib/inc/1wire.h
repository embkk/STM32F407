#ifndef WIRE_H
#define WIRE_H

#include <stdio.h>
#include "stm32f407xx.h"
// Время проверки датчика: 300 000 мкс = 300 мс
#define SENSOR_CHECK_TIME_US 250000

// 1-Wire подстановки для лучшей читабельности кода
// Примечание: Эти дефайны предполагают, что PE2 используется для 1-Wire.
// Для этого нужно настроить выход PE2 в режиме open-drain.
#define release_1wire()      (GPIOE->BSRR = GPIO_BSRR_BS2)  // Установка бита сброса (reset bit)
#define pull_low_1wire()     (GPIOE->BSRR = GPIO_BSRR_BR2)  // Установка бита установки (set bit)
#define rx_mode_1wire()      (GPIOE->MODER &= ~GPIO_MODER_MODE2_0) // Установка режима ввода
#define tx_mode_1wire()      (GPIOE->MODER |= GPIO_MODER_MODE2_0)  // Установка режима вывода
#define check_1wire()        (GPIOE->IDR & GPIO_IDR_ID2)    // Чтение состояния пина

// 1-Wire ROM команды
#define READ_ROM             0x33
#define MATCH_ROM            0x55
#define SKIP_ROM             0xCC
#define SEARCH_ROM           0xF0
#define ALARM_SEARCH         0xEC

// 1-Wire команды памяти
#define READ_SCRATCH         0xBE
#define WRITE_SCRATCH        0x4E
#define COPY_SCRATCH         0x48
#define CONVERT_T            0x44
#define RECALL_E2            0xB8
#define READ_PWR             0xB4

// 1-Wire коды ошибок
#define OK_1WIRE             0
#define NO_DEVICE_1WIRE      1
#define CRC_ERR_1WIRE        2

// параметры вычисления CRC для DS18B20
#define CRC_POLYNOM          ( (uint8_t)0x31 ) // BIN = 1_0011_0001 берем младшие 8 бит
#define CRC_LEN_8_BITS       8

// константы длин 1-Wire
#define ROM64_BYTE_LEN       8
#define ROM64_BIT_LEN        64
#define BYTE_LEN             8
#define SCRATCH_BYTE_LEN     9   



uint8_t Start_1wire(void);
void WriteByte_1wire(uint8_t byte_value);
uint8_t ReadByte_1wire(void);
uint8_t CRC_Calc(uint8_t mass[], uint8_t mass_size, uint8_t POLY);
uint8_t Read_ROM64(uint8_t *family_code, uint8_t ser_num[], uint8_t *crc);
uint8_t ReadScratchpad(uint8_t scratch_array[]);
uint8_t Convert_Temperature(void);
uint8_t WriteScratch(uint8_t tx_array[]);
void USART1_Init(void);
#endif