#include "stm32f10x.h"
void init_GPIO(void);
int main(void) {
 // Initialize GPIO for LED and buttons
 init_GPIO();
 while (1) {
if (!(GPIOA->IDR & GPIO_IDR_IDR0)) { // Button 1 is active low
 GPIOC->BSRR = GPIO_BSRR_BS13; // Turn on LED (PC13)
 GPIOC->BSRR = GPIO_BSRR_BS13; // Turn on LED (PC13)
}
// Inside your while loop
if (!(GPIOA->IDR & GPIO_IDR_IDR4)) { // Button 1 is active low
 GPIOC->BSRR = GPIO_BSRR_BR13; // Turn on LED (PC13)
}
}}
void init_GPIO(void) {
 // Enable GPIOA and GPIOC clocks
 RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPCEN;
 // Configure PA0 (Button 1) and PA4 (Button 2) as input with pull-up resistors
 GPIOA->CRL &= ~(GPIO_CRL_MODE0 | GPIO_CRL_CNF0 | GPIO_CRL_MODE4 | GPIO_CRL_CNF4);
 GPIOA->CRL |= (GPIO_CRL_CNF0_1 | GPIO_CRL_CNF4_1); // Input with pull-up/pull-down
 GPIOA->ODR |= (GPIO_ODR_ODR0 | GPIO_ODR_ODR4); // Enable pull-up resistors
 // Configure PC13 as output (for LED)
 GPIOC->CRH &= ~(GPIO_CRH_MODE13 | GPIO_CRH_CNF13);
 GPIOC->CRH |= GPIO_CRH_MODE13_1; // Output mode, max speed 2 MHz
 GPIOC->BSRR = GPIO_BSRR_BR13;
} 
