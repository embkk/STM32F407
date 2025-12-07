#include <stm32f407xx.h>
#include "buttons.h"
#include "log.h"

void RCC_Init(void);

uint32_t last_send_ms;

int main(void) {
  LOG_INIT();

  SystemInit();
  SysTick_Config(SystemCoreClock / 1000); // 1 мс
  RCC_Init();

  while(1) {
    
  }
}


void SysTick_Handler(void)
{
}
