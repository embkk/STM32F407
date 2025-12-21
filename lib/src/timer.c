#include "timer.h"

void TIM2_init(void) {
  RCC->APB1ENR  |=  RCC_APB1ENR_TIM2EN;

  /* settings timer TIM2 */
  TIM2->PSC   = 41;           // 1MHz clock
  TIM2->CR1  |= TIM_CR1_OPM;  // one pulse count mode
  TIM2->DIER |= TIM_DIER_UIE;
  TIM2->EGR  |= TIM_EGR_UG;
  TIM2->SR   &= ~TIM_SR_UIF;

  NVIC_EnableIRQ(TIM2_IRQn);
}

void TIM2_Start(uint16_t cycles_num) {
  TIM2->ARR  = cycles_num -1;
  TIM2->CNT  = 0;
  TIM2->SR  &= ~(TIM_SR_UIF); // clear UIF flag
  TIM2->CR1 |= TIM_CR1_CEN;   // timer 2 clock enable
}