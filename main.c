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


int main(void) {
  LOG_INIT();

  SystemInit();
  RCC_Init();

  USART_init();
  //DMA2_Stream0_Init();
  //DMA2_Stream7_Init();

  LOG_MESSAGE("All init success");

  char test[2] = "AB";
  while(1) {
    //test[0]++;
    USART_send_string(USART1, test);
    LOG_MESSAGE("Sent %s", test);
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

  DMA2_Stream7->PAR   =  (uint32_t)USART1_BASE; // src adr
  DMA2_Stream7->M0AR  =  (uint32_t)buffer_in;   // memory adr
  DMA2_Stream7->NDTR  =  BUFFER_LEN;                      // количество передаваемых данных
  
  DMA2_Stream7->FCR |=  DMA_SxFCR_DMDIS; // direct mode disabled in memory to memory
  DMA2_Stream7->CR  |=  (7 << DMA_SxCR_CHSEL_Pos);            // USART1_TX
  DMA2_Stream7->CR  &=  ~(DMA_SxCR_MBURST | DMA_SxCR_PBURST); // одиночная не пакет
  DMA2_Stream7->CR  &=  ~(DMA_SxCR_DBM);                      // дв. буфер выкл
  DMA2_Stream7->CR  |=  DMA_SxCR_PL_1;      //приоритет ниже, чем stream0
  DMA2_Stream7->CR  &= (~DMA_SxCR_MSIZE_0); //byte
  DMA2_Stream7->CR  &= (~DMA_SxCR_PSIZE_0); //byte

  DMA2_Stream7->CR  |= DMA_SxCR_MINC;    //инкремент памяти
  DMA2_Stream7->CR  &= ~(DMA_SxCR_PINC); //не инкремент периферии, пишем в usart DR

  DMA2_Stream7->CR  |= DMA_SxCR_CIRC;   //циклический режим
  DMA2_Stream7->CR  |= DMA_SxCR_DIR_0;   // memory > perepheral
  //DMA2_Stream7->CR  |= DMA_SxCR_TCIE;   //прерывание tr. compl

  NVIC_EnableIRQ(DMA2_Stream7_IRQn);

  DMA2_Stream7->CR   |= DMA_SxCR_EN;
}