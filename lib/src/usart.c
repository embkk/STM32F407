#include "usart.h"
#include "log.h"
#include "stm32f407xx.h"

unsigned char USART_Initialized;

void USART_send_string(USART_TypeDef *usart, const char *s) {
    while (*s) {
        while (!(usart->SR & USART_SR_TXE)); // waiting buffer
        usart->DR = *s++;
    }
}

void USART_send_bytes(USART_TypeDef *usart, const char *s, const uint32_t len) {
    for(uint32_t i = 0; i<len; i++) {
        while (!(usart->SR & USART_SR_TXE)); // waiting buffer
        usart->DR = *s++;
    }
}

void USART_init(void) { 
  if(USART_Initialized) {
    LOG_MESSAGE("USART re-initialize error");
    return;
  }

  RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
  RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

  /*
    84Mhz / 115200 / 16 = 45,572916667
    
    M = 45 (0x2D)
    F = 0,57 * 16 = 9.12 (0x9)
  */

  USART1-> BRR = 0x02D9; // бод

  //             interrupt          transmitter+   receiver+
  USART1-> CR1 = USART_CR1_RXNEIE | USART_CR1_TE | USART_CR1_RE;
  
  //              word length       parity conntrol
  USART1->CR1 &= ~(USART_CR1_M) | ~(USART_CR1_PCE);
  USART1->CR2 &= ~(USART_CR2_STOP); //1 stopbit
  NVIC_EnableIRQ(USART1_IRQn);
  USART1-> CR1 |= USART_CR1_UE; // enable USART

  //dma
  //USART1->CR3 |= USART_CR3_DMAT;

  GPIOA->MODER |= 0b10 << GPIO_MODER_MODE9_Pos;
  GPIOA->AFR[1] |= (7<<GPIO_AFRH_AFSEL9_Pos) | (7<<GPIO_AFRH_AFSEL10_Pos);
  USART_Initialized = 1;
}

/*void USART1_IRQHandler(void) {
  
  if((USART1->SR & USART_SR_RXNE) != 0) {
    uint16_t RXc = (uint16_t)(USART1->DR & (uint16_t)0x01FF);
    switch (RXc) {
      case '0': {
        // all LED reset
        GPIO_LED_off(LED01);
        GPIO_LED_off(LED02);
        GPIO_LED_off(LED03);
        break;
      }
      case '1': {
        GPIO_LED_on(LED01);
        break;
      }
      case '2': {
        GPIO_LED_on(LED02);
        break;
      }
      case '3': {
        GPIO_LED_on(LED03);
        break;
      }
      default: {
        // unknown input
        USART_send_string(USART1, "\nError. Unknown input" );
      }
    }
  }

  NVIC_ClearPendingIRQ(USART1_IRQn);
}*/

