#include "buttons.h"
#include "stm32f407xx.h"

uint16_t bound_timer;
uint32_t btn_count[3] = {0};
uint8_t btn_state[3] = {0};

void Buttons_init(void) {
  RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOEEN;

  RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
  SYSCFG->EXTICR[2] |= SYSCFG_EXTICR3_EXTI10_PE | SYSCFG_EXTICR3_EXTI11_PE;
  SYSCFG->EXTICR[3] |= SYSCFG_EXTICR4_EXTI12_PE;

  // E10-E12 input mode
  GPIOE->MODER &= ~(GPIO_MODER_MODE10 | GPIO_MODER_MODE11 | GPIO_MODER_MODE12);
}

void LED_init(void) {
  RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
  // E13-E15 output mode
  GPIOE->MODER &= ~(GPIO_MODER_MODER13_Msk | GPIO_MODER_MODER14_Msk | GPIO_MODER_MODER15_Msk);
  GPIOE->MODER |= (0b01 << GPIO_MODER_MODE13_Pos) | (0b01 << GPIO_MODER_MODE14_Pos) | (0b01 << GPIO_MODER_MODE15_Pos);
  GPIOE->BSRR |= GPIO_BSRR_BS13 | GPIO_BSRR_BS14 | GPIO_BSRR_BS15;
}


#define button(n, port) if ((GPIOE->IDR & GPIO_IDR_ID##port )==0) {\
    if(btn_count[n] < BTN_CHECK_MS) {\
      btn_count[n]++;\
    } else {\
      btn_state[n] = 1;\
    }\
  } else {\
    btn_count[n] = 0;\
    btn_state[n] = 0;\
  }

void Buttons_check(void) {
  button(0, 10);
  button(1, 11);
  button(2, 12);
}

