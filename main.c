#include <stm32f407xx.h>
#include "buttons.h"
#include "log.h"

void RCC_Init(void);
void TIM1_Init(void);
void ADC1_Init(void);
void DMA2_Stream0_Init(void);
void DMA2_Stream0_IRQHandler(void);

uint16_t buffer[8] __attribute__((section(".fast")));

int main(void) {
  LOG_INIT();

  SystemInit();
  RCC_Init();
  //SysTick_Config(84000);

  //Buttons_init();
  //EXTI_init_lines(10,11);
  //LED_init();
  TIM1_Init();
  ADC1_Init();
  DMA2_Stream0_Init();

  LOG_MESSAGE("All init success");

  while(1) {
    
  }
}

/*void ADC_IRQHandler(void) {
  TIM1->CCR4 = ( ADC1->DR * 1000 ) / 4096;
  NVIC_ClearPendingIRQ(ADC_IRQn);
}*/

void ADC1_Init(void) {
  RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;   
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

  GPIOA->MODER |= GPIO_MODER_MODE5;

  ADC->CCR |= ADC_CCR_ADCPRE; // pclk2/8
  
  ADC1->SMPR2  |= ADC_SMPR2_SMP5_2;       // 84+12 циклов
  ADC1->SQR1   |= 0 << ADC_SQR1_L_Pos;    // Длина последовательности 1
  ADC1->SQR3   |= 5 << ADC_SQR3_SQ1_Pos;  // Первая конвертация 5 канал
  
  ADC1->CR2    |= ADC_CR2_DMA | ADC_CR2_DDS;  //dma 

  ADC1->CR2    |= ADC_CR2_CONT | ADC_CR2_ADON;   //непрерывный режим | включаем модуль ацп
  ADC1->CR2    |= ADC_CR2_SWSTART;//запуск измерения
}

void TIM1_Init(void) {
  RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;

  /*GPIOE->MODER   |= GPIO_MODER_MODE14_1;
  GPIOE->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR14_1;
  GPIOE->AFR[1]  |= GPIO_AFRH_AFRH6_0;*/
  
  GPIOE->MODER   |= GPIO_MODER_MODE13_1;
  GPIOE->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR13_1;
  GPIOE->AFR[1]  |= GPIO_AFRH_AFRH5_0;

  // Захват входа
  TIM1->PSC    = 83;
  TIM1->CR1   |= TIM_CR1_CMS;
  TIM1->ARR    = 999;
  TIM1->CCR4   = 1;
  TIM1->CCMR2 |= TIM_CCMR2_OC3M;
  TIM1->CCMR2 &= ~(TIM_CCMR2_CC3S);
  TIM1->CCER  |= TIM_CCER_CC3E;
  TIM1->BDTR  |= TIM_BDTR_MOE;

  TIM1->CR1 |= TIM_CR1_CEN;

  TIM1->EGR |= TIM_EGR_UG;
}


void DMA2_Stream0_Init(void) {
  RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;

  DMA2_Stream0->PAR   =  (uint32_t)&(ADC1->DR);  // адрес периферии
  DMA2_Stream0->M0AR  =  (uint32_t)buffer;       // адрес памяти
  DMA2_Stream0->NDTR  =  8;                      // количество передаваемых данных
  
  DMA2_Stream0->FCR &=  ~(DMA_SxFCR_DMDIS);                   // прямой режим без FIFO
  DMA2_Stream0->CR  &=  ~(DMA_SxCR_CHSEL);                    // канал 0
  DMA2_Stream0->CR  &=  ~(DMA_SxCR_MBURST | DMA_SxCR_PBURST); // одиночная не пакет
  DMA2_Stream0->CR  &=  ~(DMA_SxCR_DBM);                      // дв. буфер выкл
  DMA2_Stream0->CR  |=  DMA_SxCR_PL;                          // высокий приоритет
  DMA2_Stream0->CR  |=  DMA_SxCR_MSIZE_0 | DMA_SxCR_PSIZE_0;  // полуслово полуслово

  DMA2_Stream0->CR  |= DMA_SxCR_MINC;   //инкремент памяти
  DMA2_Stream0->CR  &= ~(DMA_SxCR_PINC);//без инкремента прф

  DMA2_Stream0->CR  |= DMA_SxCR_CIRC;   //циклический режим
  DMA2_Stream0->CR  &= ~(DMA_SxCR_DIR);   //из периферии в память
  DMA2_Stream0->CR  |= DMA_SxCR_TCIE;   //прерывание tr. compl

  NVIC_EnableIRQ(DMA2_Stream0_IRQn);

  DMA2_Stream0->CR   |= DMA_SxCR_EN;
}


void DMA2_Stream0_IRQHandler(void) {
  uint8_t i;
  uint16_t ovr = 0; //oversampling
  for(i = 0; i<8; i++) {
    ovr = ovr + buffer[i];
  }

  LOG_MESSAGE("DMA IRQ");

  TIM1->CCR3 = ( (ovr/8) * 1000 ) / 4096; //вычисление

  DMA2->LIFCR |= DMA_LIFCR_CTCIF0; // очистка флага прерывания
  NVIC_ClearPendingIRQ(DMA2_Stream0_IRQn);
}

