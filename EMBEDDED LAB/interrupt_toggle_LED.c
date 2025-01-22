#include "stm32f10x.h" // Device header
 void init_GPIOC(void) {
 RCC->APB2ENR |= RCC_APB2ENR_IOPCEN; // Enable clock for GPIOC
GPIOC->CRH &= ~(GPIO_CRH_CNF13); // Clear PC13 configuration bits (input mode)
 GPIOC->CRH |= GPIO_CRH_MODE13_1; // Set PC13 as output mode, max speed 2
 MHz
 }
 void delay_ms(uint32_t delay) {
 for (uint32_t i = 0; i < delay * 4000; i++) {
 __asm("nop"); // No operation, simple delay loop
 }
 }
 void toggle_LED(int state) {
 if (state) {
 GPIOC->ODR &=~(1UL <<13); //Set PC13 low (turn LED on, active low)
 } else {
 GPIOC->ODR |= (1UL << 13); // Set PC13 high (turn LED off, active low)
 }
 }
 int main() {
 init_GPIOC(); // Initialize GPIOC pin 13
 while (1) {
 toggle_LED(1); // Turn LED on (active low)
 delay_ms(1000); // 1-second delay
 toggle_LED(0); // Turn LED off (active low)
 delay_ms(1000); // 1-second delay
 }
 }
