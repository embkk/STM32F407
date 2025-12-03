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

  LED_init();
  GPIO_LED_all_off();

  TIM2_Init();
  ADC1_Init();
  LOG_MESSAGE("ADC INIT SUCCESS");
  
  
  while(1) {
    
  }
}

void ADC_IRQHandler(void) {
    /* Bit 0 AWD: Analog watchdog flag
    This bit is set by hardware when the converted voltage crosses the values programmed in
    the ADC_LTR and ADC_HTR registers. It is cleared by software.
    0: No analog watchdog event occurred
    1: Analog watchdog event occurred*/

    if (ADC1->SR & ADC_SR_AWD) {
        GPIO_LED_off(LED02);
    } else {
        GPIO_LED_on(LED02);
    }

    ADC1->SR &= ~ADC_SR_AWD; // сброс флага AWD
    NVIC_ClearPendingIRQ(ADC_IRQn);
}

void ADC1_Init(void) {
  RCC->APB2ENR |= RCC_APB2ENR_ADC1EN; // Включение тактирования АЦП
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; // Включение тактирования порта GPIOA

  GPIOA->MODER |= GPIO_MODER_MODE5; // GPIOA_PA5 в режиме аналог (ADC1_CH5)

  ADC1->SMPR2 |= ADC_SMPR2_SMP5_0; // выбираем канал конвертирования ADC1 Channel 5 и время конвертирования 15 тактов
  ADC1->JSQR &= ~(ADC_JSQR_JL); // Длина последовательности инжектированных каналов равна 1
  ADC1->JSQR |= (5 << ADC_JSQR_JSQ4_Pos); // When JL=0 (1 injected conversion in the sequencer), the ADC converts only JSQ4[4:0] channel.

  
  ADC1->CR1 |= ADC_CR1_JAWDEN; // Analog Watchdog для инжектированных каналов
  ADC1->CR1 |= (5 << ADC_CR1_AWDCH_Pos); // канал 5 Analog Watchdog
  ADC1->CR1 |= ADC_CR1_AWDIE; // разрешение прерывания по analog watchdog
  ADC1->CR1 |= ADC_CR1_JEOCIE; // разрешение прерывания при injected end of conversion
  
  ADC1->CR1 |= ADC_CR1_RES_0; // 10 бит 1024
  ADC1->HTR = 819; // 80% от 1024
  ADC1->LTR = 102; // 10% от 1024
  
  ADC1->CR2 |= ADC_CR2_JEXTEN_0; // rising edge 
  //ADC1->CR2 |= ADC_CR2_JEXTSEL_1; //TIM2_CH1
  ADC1->CR2 |= 3 << ADC_CR2_JEXTSEL_Pos; // TIM2_TRGO
  ADC1->CR2 |= ADC_CR2_ADON; // АЦП вкл
  ADC1->CR2 |= ADC_CR2_JSWSTART; 

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

    //TIM2->DIER |= TIM_DIER_UIE; // Bit 0 UIE: Update interrupt enable

    /* Bit 0 UG: Update generation 1: Re-initialize the counter and generates an update of the registers. */
    //TIM2->EGR |= TIM_EGR_UG;
    
    TIM2->CR1 |= TIM_CR1_CEN;

    //NVIC_EnableIRQ(TIM2_IRQn);
}