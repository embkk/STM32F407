#include <stm32f407xx.h>
#include "buttons.h"
#include "log.h"
#include "usart.h"

void RCC_Init(void);
void TIM1_Init(void);
void ADC1_Init(void);
void DMA2_Stream0_Init(void);
void DMA2_Stream7_Init(void);

#define BUFFER_LEN 16

char buffer_src[BUFFER_LEN] __attribute__((section(".fast"))) = "USART-DMA OK!";
char buffer_in[BUFFER_LEN] __attribute__((section(".fast")));

uint32_t last_send_ms;

int main(void) {
  int i = 0;
  LOG_INIT();

  SystemInit();
  SysTick_Config(SystemCoreClock);
  RCC_Init();

  USART_init();

  // memory to memroy
  DMA2_Stream0_Init();
  
  for(int i=0; i<1000;i++);

  // включаем Memory to USART
  DMA2_Stream7_Init();

  while(1) {
    /* здесь ничего не нужно
    i++;
    buffer_src[0] = i;*/
  }
}

void DMA2_Stream0_Init(void) {
  RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;

  DMA2_Stream0->PAR   =  (uint32_t)buffer_src;  // Source address
  DMA2_Stream0->M0AR  =  (uint32_t)buffer_in;   // Destination address
  DMA2_Stream0->NDTR  =  BUFFER_LEN;                      // количество передаваемых данных
  
  DMA2_Stream0->FCR |=  DMA_SxFCR_DMDIS; // direct mode disabled in memory to memory
  //DMA2_Stream0->CR  &=  ~(DMA_SxCR_CHSEL);                    // канал 0
  DMA2_Stream0->CR  &=  ~(DMA_SxCR_MBURST | DMA_SxCR_PBURST); // одиночная не пакет
  DMA2_Stream0->CR  &=  ~(DMA_SxCR_DBM);                      // дв. буфер выкл
  DMA2_Stream0->CR  |=  DMA_SxCR_PL;                          // высокий приоритет
  DMA2_Stream0->CR  &= (~DMA_SxCR_MSIZE_0); //byte
  DMA2_Stream0->CR  &= (~DMA_SxCR_PSIZE_0); //byte

  DMA2_Stream0->CR  |= DMA_SxCR_MINC;   //инкремент памяти
  DMA2_Stream0->CR  |= DMA_SxCR_PINC;   //инкремент периферии (по сути памяти)

  DMA2_Stream0->CR  |= DMA_SxCR_CIRC;   //циклический режим
  DMA2_Stream0->CR  |= DMA_SxCR_DIR_1;   // memory memory
  //DMA2_Stream0->CR  |= DMA_SxCR_TCIE;   //прерывание tr. compl

  NVIC_EnableIRQ(DMA2_Stream0_IRQn);

  DMA2_Stream0->CR   |= DMA_SxCR_EN;
}

void DMA2_Stream7_Init(void) {
  RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;

  DMA2_Stream7->PAR   =  (uint32_t)&USART1->DR; // src adr
  DMA2_Stream7->M0AR  =  (uint32_t)buffer_in;   // memory adr
  DMA2_Stream7->NDTR  =  BUFFER_LEN;                      // количество передаваемых данных
  
  DMA2_Stream7->FCR &= ~(DMA_SxFCR_DMDIS); // direct mode enabled
  DMA2_Stream7->CR  |=  (4 << DMA_SxCR_CHSEL_Pos);            // USART1_TX
  DMA2_Stream7->CR  &=  ~(DMA_SxCR_MBURST | DMA_SxCR_PBURST); // одиночная не пакет
  DMA2_Stream7->CR  &=  ~(DMA_SxCR_DBM);                      // дв. буфер выкл
  DMA2_Stream7->CR  |=  DMA_SxCR_PL_1;      //приоритет ниже, чем stream0
  DMA2_Stream7->CR  &= (~DMA_SxCR_MSIZE); //byte
  DMA2_Stream7->CR  &= (~DMA_SxCR_PSIZE); //byte

  DMA2_Stream7->CR  |= DMA_SxCR_MINC;    //инкремент памяти
  DMA2_Stream7->CR  &= ~(DMA_SxCR_PINC); //не инкремент периферии, пишем в usart DR

  DMA2_Stream7->CR  &= ~DMA_SxCR_CIRC;   //циклический режим off
  DMA2_Stream7->CR  |= DMA_SxCR_DIR_0;   // memory > perepheral
  DMA2_Stream7->CR  |= DMA_SxCR_TCIE;   //прерывание tr. compl

  NVIC_EnableIRQ(DMA2_Stream7_IRQn);
}

void DMA2_Stream7_IRQHandler(void) {
  LOG_MESSAGE("DMA2_Stream7_IRQHandler");
  if(DMA2->HISR & DMA_HISR_TCIF7) {
    //очистка флага
    DMA2->HIFCR |= DMA_HIFCR_CTCIF7;
    //отключение
    DMA2_Stream7->CR &= ~DMA_SxCR_EN;
    NVIC_ClearPendingIRQ(DMA2_Stream7_IRQn);
  }
}

void DMA2_Stream7_Activate(void) {
  if(DMA2_Stream7->CR & DMA_SxCR_EN) {
    LOG_MESSAGE("%d Busy", last_send_ms);
    return;
  }
    // Перезаряжаем длину
  DMA2_Stream7->NDTR = BUFFER_LEN;

  // Запускаем передачу
  DMA2_Stream7->CR |= DMA_SxCR_EN;
}

void SysTick_Handler(void)
{
  last_send_ms++;
  if(last_send_ms<1000) return;
  last_send_ms = 0;
  DMA2_Stream7_Activate();
}
