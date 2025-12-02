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
  RCC->APB2ENR |= RCC_APB2ENR_ADC1EN; // Включение тактирования АЦП
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; // Включение тактирования порта GPIOA

  GPIOA->MODER |= GPIO_MODER_MODE5; // GPIOA_PA5 в режиме альтен. функции (ADC1_CH5)

  ADC1->SMPR2 |= ADC_SMPR2_SMP5_0; // выбираем канал конвертирования ADC1 Channel 5 и время конвертирования 15 тактов
  ADC1->JSQR &= ~(ADC_JSQR_JL); // Длина последовательности инжектированных каналов равна 1
  ADC1->JSQR |= (5 << ADC_JSQR_JSQ4_Pos); // выбрать АЦП канал 5 для конвертирования в последовательности

  // Разрядность 10^2 = 1024  
  ADC1->CR1 |= ADC_CR1_RES_0; // Выбрали 10-бит разрядность АЦП
  
  ADC1->CR1 |= ADC_CR1_JAWDEN; // Включили Analog Watchdog для инжектированных каналов
  ADC1->CR1 |= (5 << ADC_CR1_AWDCH_Pos); // Для канала 5 работает Analog Watchdog
  
  ADC1->HTR = 819; // 80% Задали верхний порог срабатывания Analog Watchdog
  ADC1->LTR = 102; // 10% Задали нижний порог срабатывания Analog Watchdog

  ADC1->CR2 |= ADC_CR2_JEXTEN_1; // Включен внешний тригер для запуска конвертации АЦП
  ADC1->CR2 |= ADC_CR2_JEXTSEL_1;
  ADC1->CR2 |= ADC_CR2_ADON; // АЦП включен
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