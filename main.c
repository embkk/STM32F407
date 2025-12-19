#include <stm32f407xx.h>
#include "log.h"
 
void RCC_Init(void);


int main(void) {
  LOG_INIT();

  SystemInit();
  SysTick_Config(84000);
  RCC_Init();

  while(1) {

  }
}





void SysTick_Handler(void)
{

}
