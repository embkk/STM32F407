#include <stm32f407xx.h>
#include "buttons.h"
#include "log.h"

void RCC_Init(void);
void TIM2_Init(void);
void ADC1_Init(void);
void ADC_IRQHandler(void);

int main(void) {
  LOG_INIT();

  SystemInit();
  RCC_Init();
  SysTick_Config(84000);

  TIM2_Init();
  ADC1_Init();

  while(1) {
    
  }
}

void ADC_IRQHandler(void) {
  LOG_MESSAGE("IRQ ");
}

void ADC1_Init(void) {
  RCC->APB2ENR |= RCC_APB2ENR_ADC1EN; // Включение тактирования АЦП
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; // Включение тактирования порта GPIOA

  GPIOA->MODER |= GPIO_MODER_MODE5; // GPIOA_PA5 в режиме аналог (ADC1_CH5)

  ADC1->SMPR2 |= ADC_SMPR2_SMP5_0; // выбираем канал конвертирования ADC1 Channel 5 и время конвертирования 15 тактов
  ADC1->JSQR &= ~(ADC_JSQR_JL); // Длина последовательности инжектированных каналов равна 1
  ADC1->JSQR |= (5 << ADC_JSQR_JSQ4_Pos); // выбрать АЦП канал 5 для конвертирования в последовательности

  
  ADC1->CR1 |= ADC_CR1_JAWDEN; // Analog Watchdog для инжектированных каналов
  ADC1->CR1 |= (5 << ADC_CR1_AWDCH_Pos); // канал 5 Analog Watchdog
  ADC1->CR1 |= ADC_CR1_AWDIE; // разрешение прерывания по analog watchdog
  ADC1->CR1 |= ADC_CR1_JEOCIE; // разрешение прерывания при injected end of conversion
  
  ADC1->CR1 |= ADC_CR1_RES_0; // 10 бит 1024
  ADC1->HTR = 819; // 80% от 1024
  ADC1->LTR = 102; // 10% от 1024
  
  ADC1->CR2 |= ADC_CR2_JEXTEN_1; // falling edge
  ADC1->CR2 |= 0b0110 << ADC_CR2_JEXTSEL_Pos; // TIM2_TRGO
  ADC1->CR2 |= ADC_CR2_ADON; // АЦП вкл

  NVIC_EnableIRQ(ADC_IRQn);
}

void TIM2_Init(void)
{
    // When using triggered injection, one must ensure that the interval between trigger events is
    // longer than the injection sequence.

    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;   // тактирование таймера

    TIM2->PSC = 83;               // 84 MHz → 1 MHz
    TIM2->ARR = 999;              // период 1 мс (1000 тактов)

    // 010: Update - The update event is selected as trigger output (TRGO).
    // For instance a master timer can then be used as a prescaler for a slave timer.
    TIM2->CR2 &= ~TIM_CR2_MMS;    
    TIM2->CR2 |= 0b010 << TIM_CR2_MMS_Pos;

    TIM2->DIER |= TIM_DIER_UIE; // Bit 0 UIE: Update interrupt enable

    /* Bit 0 UG: Update generation 1: Re-initialize the counter and generates an update of the registers. */
    TIM2->EGR |= TIM_EGR_UG;
    
    TIM2->CR1 |= TIM_CR1_CEN;

    NVIC_EnableIRQ(TIM2_IRQn);
}
/*void TIM2_IRQHandler(void)
{
    if (TIM2->SR & TIM_SR_UIF)
    {
        TIM2->SR &= ~TIM_SR_UIF;
        LOG_MESSAGE("TIM2\n");
    }
}
*/