#include "main.h"
#include "lib/SD/sdcard.h"
#include <stdint.h>

#define BUFFER_SIZE_BYTES   (uint16_t)2048
#define START_SECTOR_NUM    (uint32_t)4    //0-3 sectors for FAT markup

uint8_t readData_8[BUFFER_SIZE_BYTES];
uint8_t writeBuffer_bytes[BUFFER_SIZE_BYTES];

SD_CardInfo SDCardInfo;



int main(void) {

  SystemInit();
  RCC_Init();

  SysTick_Config(SYSTICK_TIMER_CONST);

  while(1) {
  }
}

void SysTick_Handler(void)
{
  timer_counter();
}
