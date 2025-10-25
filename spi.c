#include "spi.h"
#include "log.h"

uint8_t w25send(uint8_t data) {
  wait_while(SPI2->SR & SPI_SR_BSY);
  SPI2->CR1 &= ~SPI_CR1_DFF;
  wait_while((SPI2->SR & SPI_SR_TXE) == 0);
  SPI2->DR = data;
  wait_while((SPI2->SR & SPI_SR_RXNE) == 0);
  uint32_t received_data = SPI2->DR;
  LOG_MESSAGE("W25send tx %d / rx %d", data, received_data);
  return received_data;
}

uint16_t w25send_16bit(uint16_t data) {
  wait_while(SPI2->SR & SPI_SR_BSY);
  SPI2->CR1 |= SPI_CR1_DFF;
  LOG_MESSAGE("W25send 16bit %p", data);
  wait_while((SPI2->SR & SPI_SR_TXE) == 0);
  SPI2->DR = data;
  wait_while((SPI2->SR & SPI_SR_RXNE) == 0);
  return SPI2->DR;
}

void SPI2_Init(uint32_t addr) {
  LOG_MESSAGE("SPI init...");
  RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN | RCC_AHB1ENR_GPIOEEN;

  GPIOC->MODER |= GPIO_MODER_MODE2_1 | GPIO_MODER_MODE3_1;
  GPIOC->AFR[0] |= (5<<GPIO_AFRL_AFSEL3_Pos) | (5<<GPIO_AFRL_AFSEL2_Pos);
  GPIOC->PUPDR |= GPIO_PUPDR_PUPD3_1 | GPIO_PUPDR_PUPD2_1;

  GPIOB->MODER |= GPIO_MODER_MODE10_1;
  GPIOB->AFR[1] = (5<<GPIO_AFRH_AFSEL10_Pos);
  GPIOB->PUPDR |= GPIO_PUPDR_PUPD10_1;

  GPIOE->MODER |= GPIO_MODER_MODE3_0;
  GPIOE->OTYPER &= ~(GPIO_OTYPER_OT3);
  GPIOE->PUPDR |= GPIO_PUPDR_PUPD3_1;
  GPIOE->BSRR |= GPIO_BSRR_BS3;

  RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;
  
  SPI2->CR1 = 0;
  SPI2->CR1 |= SPI_CR1_BR_0 | SPI_CR1_BR_2 | SPI_CR1_MSTR | SPI_CR1_SSM | SPI_CR1_SSI;
  //SPI2->CR1 &= ~(SPI_CR1_DFF);

  //SPI2->CR1 |= SPI_CR1_CPOL | SPI_CR1_CPHA;
  SPI2->CR1 |= SPI_CR1_SPE;

  w25_open(
    // Enable reset
    w25send(EN_RST);
  );

  w25_open(
    // Reset
    w25send(RST);
  );

  w25_open(
    // Write enable
    w25send(WR_EN);
  );

  w25_open(
    // Sector erase
    w25send(SECT_ER);
    w25send_addr(addr);
  );

  w25_open(
    // Read status register
    w25send(RD_SR1);
    while( (w25send(0x00) & 0x01) == 1 );
  );

  w25_open(
    // Write Enable
    w25send(WR_EN);
  );
  LOG_MESSAGE("SPI init finished.");
}
