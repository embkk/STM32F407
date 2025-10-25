#include <stm32f407xx.h>
#include "buttons.h"
#include "gpio.h"
#include "log.h"

void RCC_Init(void);
void TIM1_Init(void);
void TIM2_Init(void);

uint32_t time_ms;
uint32_t sec_delay;
uint32_t capture;
//uint32_t delay_500ms;
//uint32_t delay_10ms;

int main(void) {
  SystemInit();
  RCC_Init();
  SysTick_Config(168000);
  
  LED_init();
  TIM1_Init();
  TIM2_Init();

  LOG_INIT();

  while(1) {
    if(sec_delay>=1000) {
      sec_delay = 0;
      GPIO_LED_toggle(LED01);
    }
  }
}

void SysTick_Handler(void) {
  time_ms++;
  sec_delay++;
}

void TIM1_Init(void) {
  RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;

  // PA8 alt function 1
  //RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; 
  //GPIOA->MODER |= GPIO_MODER_MODER8_1;
  //GPIOA->AFR[1] |= (1 << GPIO_AFRH_AFSEL8_Pos);

  TIM1->SMCR |= 0b001; // internal trigger 1
  TIM1->SMCR |= 0b111; // SMS = 111 (ECLK Mode 2)
  //TIM1->PSC = 83;
  //TIM1->ARR = 999;

  // Захват входа
  TIM1->CCMR1 |= TIM_CCMR1_CC1S; // захват входа
  TIM1->CCER &= ~TIM_CCER_CC1P; // Capture/Compare 1 output polarity active low
  TIM1->CCER |= TIM_CCER_CC1E; // capture/compare enable
  
  // прерывание по захвату
  TIM1->DIER |= TIM_DIER_CC1IE; // Прерывание по захвату
  NVIC_EnableIRQ(TIM1_CC_IRQn); // Включение в NVIC

  TIM1->CR1 |= TIM_CR1_CEN; // Включение TIM1
}

void TIM2_Init(void) {
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; // Включение TIM2

    TIM2->PSC = 83; // Предделитель (1 МГц при 84 МГц на APB1)
    TIM2->ARR = 999; // Период 1 мс (1 кГц)

    // Настройка TIM2 как мастер: вывод Update Event на TRGO
    TIM2->CR2 |= TIM_CR2_MMS_1; // MMS = 010 (Update Event на TRGO)

    TIM2->DIER |= TIM_DIER_UIE;
    NVIC_EnableIRQ(TIM2_IRQn);

    TIM2->CR1 |= TIM_CR1_CEN; // Включение TIM2
}

/*void X(void) {
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
}*/

void TIM1_CC_IRQHandler(void) {
    if (TIM1->SR & TIM_SR_CC1IF) {
        capture = TIM1->CCR1; // Сохраняем значение захвата
        GPIO_LED_toggle(LED01); // Мигаем LED01 при каждом захвате
        TIM1->SR &= ~TIM_SR_CC1IF; // Сброс флага
        LOG_MESSAGE("TIM1 Capture: %lu\n", capture); // Логируем для отладки
    }
}

void TIM2_IRQHandler(void) {
    static uint32_t tim2_count = 0;
    if (TIM2->SR & TIM_SR_UIF) {
        tim2_count++;
        if (tim2_count >= 500) { // 500 мс (500 событий по 1 мс)
            GPIO_LED_toggle(LED02); // Мигаем LED02
            tim2_count = 0;
        }
        TIM2->SR &= ~TIM_SR_UIF; // Сброс флага
    }
}