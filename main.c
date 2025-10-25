#include <stm32f407xx.h>
#include "buttons.h"
#include "log.h"

void RCC_Init(void);
void TIM1_Init(void);

uint32_t time_ms;
uint32_t delay_500ms;
uint32_t delay_10ms;

int main(void) {
  SystemInit();
  RCC_Init();
  SysTick_Config(168000);
  
  LED_init();
  TIM1_Init();

  LOG_INIT();

 
  while(1) {
    if(delay_500ms <= time_ms) {
      GPIO_LED_toggle(LED01);
      //GPIO_pin_io_status(O, E, 13)

      delay_500ms = time_ms + 500;
    }
    if(delay_10ms<=time_ms) {
      if(TIM1->CCR4 >=999) {
        TIM1->CCR4 = 1;
      } else {
        TIM1->CCR4 += 5;
      }
      delay_10ms = time_ms +10;
    }
  }
}

void SysTick_Handler(void) {
  time_ms++;
}

void TIM1_Init(void) {
  RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN; 

  GPIOE->MODER &= (~GPIO_MODER_MODE14_Msk);
  GPIOE->MODER |= (0b10 << GPIO_MODER_MODE14_Pos);

  GPIOE->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR14_1;
  GPIOE->AFR[1] |= GPIO_AFRH_AFRH6_0;

  TIM1->PSC = 83;
  TIM1->CR1 |= TIM_CR1_CMS;
  TIM1->ARR = 999;
  TIM1->CCR4 = 1;
  TIM1->CCMR2 |= TIM_CCMR2_OC4M;
  TIM1->CCMR2 &= ~(TIM_CCMR2_CC4S);
  TIM1->CCER |= TIM_CCER_CC4E;
  TIM1->BDTR |= TIM_BDTR_MOE;

  TIM1->CR1 |= TIM_CR1_CEN;
  TIM1->EGR |= TIM_EGR_UG;
}