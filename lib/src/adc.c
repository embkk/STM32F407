#include "adc.h"
#include "stm32f407xx.h"

/*void ADC_IRQHandler(void) {
  TIM1->CCR4 = ( ADC1->DR * 1000 ) / 4096;
  NVIC_ClearPendingIRQ(ADC_IRQn);
}*/

void ADC1_Init(void) {
  RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;   
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

  GPIOA->MODER |= GPIO_MODER_MODE5;
  
  ADC1->SMPR2  |= ADC_SMPR2_SMP5_0;       // 15+12 циклов
  ADC1->SQR1   |= ~(ADC_SQR1_L);          // Длина последовательности 1
  ADC1->SQR3   |= 5 << ADC_SQR3_SQ1_Pos;  // Первая конвертация 5 канал
  //ADC1->CR1    |= ADC_CR1_EOCIE;          // прерывание по завершению преобразования
  
  NVIC_EnableIRQ(ADC_IRQn);

  ADC1->CR2    |= ADC_CR2_CONT | ADC_CR2_ADON;   //непрерывный режим | включаем модуль ацп
  ADC1->CR2    |= ADC_CR2_SWSTART;//запуск измерения
}