
#include "main.h"
void TIM10_Init(void)
{
  RCC->APB2ENR|=RCC_APB2ENR_TIM10EN;
  TIM10->PSC=84-1;
  TIM10->ARR = 0xFFFF; 
  TIM10->CR1 |= TIM_CR1_CEN; 
}