#include <stm32f407xx.h>
#include "buttons.h"
#include "gpio.h"
#include "log.h"
#include "exti.h"

void RCC_Init(void);
void TIM1_Init(void);
void TIM2_Init(void);
void OnButtonPressed(uint8_t);

uint32_t time_ms;
uint32_t sec_delay;

uint32_t capture_ms;
uint32_t capture_test_ms;
uint8_t capture_mode;


//uint32_t delay_500ms;
//uint32_t delay_10ms;

int main(void) {
  SystemInit();
  RCC_Init();
  SysTick_Config(168000);

  Buttons_init();
  EXTI_init_lines(10,11);
  LED_init();
  TIM1_Init();
  TIM2_Init();

  LOG_INIT();

  while(1) {
    if(sec_delay>=1000) {
      sec_delay = 0;
      GPIO_LED_toggle(LED03);
    }
  }
}

void OnButtonPressed(uint8_t btn1) {
  if(btn1) {
    //capture_mode = 0;
    LOG_MESSAGE("Capture result: %lu checktest %lu", capture_ms, capture_test_ms);
  } else {
    capture_mode = 1;
    capture_test_ms = 0;
    capture_ms = 0;
    TIM1->CR1 |= TIM_CR1_CEN;
    TIM2->CR1 |= TIM_CR1_CEN;
  }
}

void EXTI15_10_IRQHandler(void) {
  
  EXTI_handle(10, OnButtonPressed(0));
  EXTI_handle(11, OnButtonPressed(1));

}


void SysTick_Handler(void) {
  time_ms++;
  sec_delay++;
  if(capture_mode) {
    capture_test_ms++;
  }
}

void TIM1_Init(void) {
  RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;

  // PA8 alt function 1
  //RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; 
  //GPIOA->MODER |= GPIO_MODER_MODER8_1;
  //GPIOA->AFR[1] |= (1 << GPIO_AFRH_AFSEL8_Pos);

  TIM1->SMCR |= 0b001 << TIM_SMCR_TS_Pos; // internal trigger 1
  TIM1->SMCR |= 0b111 << TIM_SMCR_SMS_Pos; // SMS = 111 (ECLK Mode 2)
  //TIM1->PSC = 83;
  TIM1->ARR = 0xFFFF; //max limit

  // Захват входа
  TIM1->CCMR1 |= TIM_CCMR1_CC1S; // захват входа
  TIM1->CCER &= ~TIM_CCER_CC1P; // Capture/Compare 1 output polarity active low
  TIM1->CCER |= TIM_CCER_CC1E; // capture/compare enable
  
  // прерывание по захвату
  TIM1->DIER |= TIM_DIER_CC1IE; // Прерывание по захвату
  NVIC_EnableIRQ(TIM1_CC_IRQn); // Включение в NVIC

  //TIM1->CR1 |= TIM_CR1_CEN; // Включение TIM1
}

void TIM2_Init(void) {
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; // Включение TIM2

    TIM2->PSC = 83; // Предделитель (1 МГц при 84 МГц на APB1)
    TIM2->ARR = 999; // Период 1 мс (1 кГц)

    // Настройка TIM2 как мастер: вывод Update Event на TRGO
    TIM2->CR2 |= TIM_CR2_MMS_1; // MMS = 010 (Update Event на TRGO)

    TIM2->DIER |= TIM_DIER_UIE;
    NVIC_EnableIRQ(TIM2_IRQn);

    //TIM2->CR1 |= TIM_CR1_CEN; // Включение TIM2
}

void TIM1_CC_IRQHandler(void) {
    static uint32_t tim1_count = 0;
    if (TIM1->SR & TIM_SR_CC1IF) {
        capture_ms++;
        tim1_count++;
        if (tim1_count >= 500) {
          GPIO_LED_toggle(LED01);
          tim1_count = 0;
        }
        TIM1->SR &= ~TIM_SR_CC1IF;
    }
}

/*void TIM2_IRQHandler(void) {
    static uint32_t tim2_count = 0;
    if (TIM2->SR & TIM_SR_UIF) {
        
        tim2_count++;
        if (tim2_count >= 500) {
            GPIO_LED_toggle(LED02);
            tim2_count = 0;
        }
        TIM2->SR &= ~TIM_SR_UIF; // Сброс флага
    }
}*/