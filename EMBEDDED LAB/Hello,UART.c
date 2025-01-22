 #include "stm32f10x.h"
 #include <stdint.h>
 #define BAUD_RATE 9600 // Define the baud rate
 #define SYSCLK 8000000 // System clock frequency (8 MHz)
 void initSysTick(uint32_t ticks);
 void delayMicroseconds(uint32_t value);
 void UART_SendString(const char *message);
 int main() {
 // Initialize SysTick for delays
 initSysTick(SYSCLK / 8 / 1000000); // Configure SysTick for 1-microsecond ticks
 // Simulate UART transmission
 UART_SendString("Hello, UART!");
 while (1) {
 // Infinite loop
 }
 }
void initSysTick(uint32_t ticks) {
 SysTick->CTRL = 0;
 // Disable SysTick
 SysTick->LOAD = ticks- 1;
 SysTick->VAL = 0;
 // Set reload register
 // Reset the current value register
 SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk; // Enable SysTick
 }
 void delayMicroseconds(uint32_t value) {
 while (value > 0) {
 while ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0) {
 // Wait for the COUNTFLAG to beset
 }
 value--;
 }
 }
 void UART_SendString(const char *message) {
 // Calculate the delay per character based on the baud rate
 uint32_t charDelay = (1000000 * 10) / BAUD_RATE; // 10 bits (1 start, 8 data, 1 stop)
 while (*message) {
 // Simulate sending a character
 putchar(*message); // Use putchar to send the character (could replace with GPIO/USART
 hardware)
 fflush(stdout); // Ensure the character is printed immediately
 delayMicroseconds(charDelay); // Simulated delay for UART
 message++;
 // Move tothe next character
 }
 }