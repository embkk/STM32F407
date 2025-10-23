#include <stm32f407xx.h>
#define TIME 500000

// EXTI handling
#define handle_exti(line, callback) if (EXTI->PR & EXTI_PR_PR##line) {\
    callback; \
    clear_exti_ps(line);\
}
#define clear_exti_ps(line) EXTI->PR |= EXTI_PR_PR##line

// behaviour
#define toggle_pin(port, pin) GPIO##port->BSRR = GPIO##port->ODR & GPIO_ODR_OD##pin ? GPIO_BSRR_BR##pin : GPIO_BSRR_BS##pin

uint32_t t;
uint32_t last_exti;
uint32_t last_exti_treshold = 100000;

void RCC_Init(void);

int main(void) {
  
  SystemInit();
  RCC_Init();

  RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
  SYSCFG->EXTICR[2] |= SYSCFG_EXTICR3_EXTI10_PE | SYSCFG_EXTICR3_EXTI11_PE;
  SYSCFG->EXTICR[3] |= SYSCFG_EXTICR4_EXTI12_PE;

  __enable_irq();

  // pending reset
  EXTI->PR |= EXTI_PR_PR10 | EXTI_PR_PR11 | EXTI_PR_PR12;
  
  EXTI->FTSR |= EXTI_FTSR_TR10 | EXTI_PR_PR11 | EXTI_PR_PR12;
  EXTI->IMR |= EXTI_IMR_IM10 | EXTI_IMR_IM11 | EXTI_IMR_IM12;
  NVIC_EnableIRQ(EXTI15_10_IRQn);

  RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOEEN | RCC_AHB1ENR_GPIOBEN ;

  // E13-E15 output mode
  GPIOE->MODER |= GPIO_MODER_MODE13_0 | GPIO_MODER_MODE14_0 | GPIO_MODER_MODE15_0;
  // E10-E12 input mode
  GPIOE->MODER &= ~(GPIO_MODER_MODE10 | GPIO_MODER_MODE11 | GPIO_MODER_MODE12);
  
  GPIOE->BSRR |= GPIO_BSRR_BS13 | GPIO_BSRR_BS14 | GPIO_BSRR_BS15;


  //b0 output
  GPIOB->MODER &= ~GPIO_MODER_MODE0;
  GPIOB->MODER |= GPIO_MODER_MODE0_0; 
  GPIOB->OTYPER &= ~GPIO_OTYPER_OT0; // b0 push-pull (no sence?)
  GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD0; // b0 no-pull

  //b1 input
  GPIOB->MODER &= ~GPIO_MODER_MODE1;
  GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD1;
  GPIOB->PUPDR |= GPIO_PUPDR_PUPD1_1; // b1 pull-down


  while(1) {
    t++;
    
    if(t==0) {
      //variable t will wraparound when overflow
      last_exti = 0; // clear "timstamp"
    }
  }
}

void scenario(void) {
  // change B0
  toggle_pin(B, 0);

  // read B1
  uint32_t is_b1_high = GPIOB->IDR & GPIO_IDR_ID1;
  
  toggle_pin(E, 13); // LED01 always

  if(is_b1_high) {
    toggle_pin(E, 14); // LED02 when B1 high only
  }
}

void EXTI15_10_IRQHandler(void) {
  // filter contact bounce
  if(t-last_exti<last_exti_treshold) return;

  uint32_t i=0;
  
  handle_exti(10, scenario());
  handle_exti(11, toggle_pin(E,14));
  handle_exti(12, toggle_pin(E,15));

  last_exti = t;
}