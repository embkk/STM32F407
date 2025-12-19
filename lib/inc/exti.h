#ifndef EXTI_H
#define EXTI_H

#include "validation.h"
#include "tools.h"

#define BTN_THRESHOLD 200

// init signle EXTI line
#define EXTI_init_line(line) EXTI->PR |= EXTI_PR_PR##line; \
_Static_assert(IS_VALID_PIN(line), "Invalid EXTI line: " #line); \
  EXTI->FTSR |= EXTI_FTSR_TR##line; \
  EXTI->IMR |= EXTI_IMR_IM##line;

// init multiple EXTI lines
#define EXTI_init_lines(...) FOR_EACH(EXTI_init_line, __VA_ARGS__)

// handle EXTI
#define EXTI_handle(line, callback) \
_Static_assert(IS_VALID_PIN(line), "Invalid EXTI line: " #line); \
_Static_assert(IS_FUNCTION(callback), "Callback is not a function: " #callback); \
if (EXTI->PR & EXTI_PR_PR##line) {\
    callback; \
    EXTI_clear_ps(line);\
}

// clear pending EXTI signal
#define EXTI_clear_ps(line) \
_Static_assert(IS_VALID_PIN(line), "Invalid EXTI line: " #line); \
EXTI->PR |= EXTI_PR_PR##line

#endif