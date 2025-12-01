#include <stm32f407xx.h>
#include "buttons.h"
#include "log.h"

void RCC_Init(void);
void TIM1_Init(void);
void ADC1_Init(void);
void ADC_IRQHandler(void);

int main(void) {
  LOG_INIT();

  SystemInit();
  RCC_Init();
  SysTick_Config(84000);

  //Buttons_init();
  //EXTI_init_lines(10,11);
  //LED_init();
  TIM1_Init();
  ADC1_Init();

  while(1) {
    
  }
}

void ADC_IRQHandler(void) {
  TIM1->CCR4 = ( ADC1->DR * 1000 ) / 4096;
  NVIC_ClearPendingIRQ(ADC_IRQn);
}

void ADC1_Init(void) {
  RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;   
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

  GPIOA->MODER |= GPIO_MODER_MODE5;
  
  ADC1->SMPR2  |= ADC_SMPR2_SMP5_0;       // 15+12 циклов
  ADC1->SQR1   |= ~(ADC_SQR1_L);          // Длина последовательности 1
  ADC1->SQR3   |= 5 << ADC_SQR3_SQ1_Pos;  // Первая конвертация 5 канал
  ADC1->CR1    |= ADC_CR1_EOCIE;          // прерывание по завершению преобразования
  
  NVIC_EnableIRQ(ADC_IRQn);

  ADC1->CR2    |= ADC_CR2_CONT | ADC_CR2_ADON;   //непрерывный режим | включаем модуль ацп
  ADC1->CR2    |= ADC_CR2_SWSTART;//запуск измерения
}

void TIM1_Init(void) {
  RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;

  GPIOE->MODER   |= GPIO_MODER_MODE14_1;
  GPIOE->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR14_1;
  GPIOE->AFR[1]  |= GPIO_AFRH_AFRH6_0;
  
  // Захват входа
  TIM1->PSC    = 83;
  TIM1->CR1   |= TIM_CR1_CMS;
  TIM1->ARR    = 999;
  TIM1->CCR4   = 1;
  TIM1->CCMR2 |= TIM_CCMR2_OC4M;
  TIM1->CCMR2 &= ~(TIM_CCMR2_CC4S);
  TIM1->CCER  |= TIM_CCER_CC4E;
  TIM1->BDTR  |= TIM_BDTR_MOE;

  TIM1->CR1 |= TIM_CR1_CEN;

  TIM1->EGR |= TIM_EGR_UG;
}