#ifndef GPIO_H
#define GPIO_H

#include "validation.h"
#include "stm32f407xx.h"

#define LED01 13
#define LED02 14
#define LED03 15

#define LED(n) n == 0 ? LED01 : n==1 ? LED02 : LED03

// get pin status (only Input and Output mode supported)
// asserts not supported cause usage "if(GPIO_pin_io_status)"
#define GPIO_pin_io_status(mode, port, pin) \
(GPIO##port->mode##DR & GPIO_##mode##DR_##mode##D##pin)

// toggle pin
#define GPIO_pin_toggle(mode, port, pin) \
_Static_assert(IS_VALID_PORT(port), "Invalid port: "#port);\
_Static_assert(IS_VALID_PIN(pin), "Invalid pin: "#pin);\
GPIO##port->BSRR |= (GPIO##port->mode##DR & GPIO_##mode##DR_##mode##D##pin) ? GPIO_BSRR_BR##pin : GPIO_BSRR_BS##pin

#define GPIO_pin_cond(port, pin, cond) \
if(cond) { GPIO_pin_set(port, pin); } \
else { GPIO_pin_reset(port, pin); }

// set pin to BS
#define GPIO_pin_set(port, pin) \
_Static_assert(IS_VALID_PORT(port), "Invalid port: "#port);\
_Static_assert(IS_VALID_PIN(pin), "Invalid pin: "#pin);\
GPIO##port->BSRR |= GPIO_BSRR_BS##pin

// set pin to BR
#define GPIO_pin_reset(port, pin) \
_Static_assert(IS_VALID_PORT(port), "Invalid port: "#port);\
_Static_assert(IS_VALID_PIN(pin), "Invalid pin: "#pin);\
GPIO##port->BSRR |= GPIO_BSRR_BR##pin

// LED toggle sugar
#define GPIO_LED_toggle(led) GPIO_pin_toggle(O, E, led)
#define GPIO_LED_off(led) GPIO_pin_set(E, led)
#define GPIO_LED_on(led) GPIO_pin_reset(E, led)

#define GPIO_LED_all_on() GPIO_LED_on(LED01); GPIO_LED_on(LED02); GPIO_LED_on(LED03)
#define GPIO_LED_all_off() GPIO_LED_off(LED01); GPIO_LED_off(LED02); GPIO_LED_off(LED03)

#endif

