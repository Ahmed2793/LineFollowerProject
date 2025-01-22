 #include "stm32f10x.h" // Include CMSIS library for STM32F1
 #include <stdio.h>
 // Include for sprintf
 void SystemClock_Config(void);
 void GPIO_Init(void);
 void ADC1_Init(void);
 void TIM3_Init(void);
 void UART_Init(void);
 void delay_ms(uint32_t ms);
 void UART_SendString(const char *str);
 int main(void) {
 SystemClock_Config(); // Configure System Clock
 GPIO_Init();
 // Initialize GPIO
 ADC1_Init();
 UART_Init();
 // Initialize ADC
 // Initialize UART
 // Start ADC Conversion
 ADC1->CR2 |= ADC_CR2_ADON; //EnableADC
 ADC1->CR2 |= ADC_CR2_SWSTART; // Start ADC conversion
 char buffer[50]; // Buffer for UART output
 while (1) {
 // Wait for ADC conversion to complete
 while (!(ADC1->SR & ADC_SR_EOC)); // Wait for End of Conversion
 uint16_t adcValue = ADC1->DR; // Read ADC value
 // Convert ADC value to voltage (0-3.3V)
 float voltage = (adcValue * 3.3f) / 4095.0f;
 // Format the voltage as a string
 sprintf(buffer, "Voltage: %.2f V\r\n", voltage);
 // Send the voltage over UART
 UART_SendString(buffer);
 delay_ms(500); // Delay for readability
 }
 }
 /* System Clock Configuration */
 void SystemClock_Config(void) {
 RCC->CR |= RCC_CR_HSION; // Enable HSI
 while (!(RCC->CR & RCC_CR_HSIRDY)); // Wait until HSI is ready
RCC->CFGR &= ~RCC_CFGR_SW; //Clear SWbits
 RCC->CFGR |= RCC_CFGR_SW_HSI; // Select HSI as system clock
 while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI); // Wait for HSI
 }
 /* GPIO Initialization */
 void GPIO_Init(void) {
 // Enable GPIOC clock
 RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
 // Configure PC13 as output (LED)
 GPIOC->CRH &= ~GPIO_CRH_MODE13;
 GPIOC->CRH |= GPIO_CRH_MODE13_1; // Output mode, max speed 2 MHz
 GPIOC->CRH &= ~GPIO_CRH_CNF13; // General-purpose output push-pull
 }
 /* ADC Initialization */
 void ADC1_Init(void) {
 // Enable ADC1 and GPIOA clock
 RCC->APB2ENR |= RCC_APB2ENR_ADC1EN | RCC_APB2ENR_IOPAEN;
 // Configure PA0 as analog input
 GPIOA->CRL &= ~GPIO_CRL_MODE0;
 GPIOA->CRL &= ~GPIO_CRL_CNF0;
 // ADC configuration
 ADC1->CR2 |= ADC_CR2_ADON; //EnableADC
 ADC1->SMPR2 |= ADC_SMPR2_SMP0; // Sampling time for channel 0
 }
 /* UART Initialization */
 void UART_Init(void) {
 // Enable USART1 and GPIOA clock
 RCC->APB2ENR |= RCC_APB2ENR_USART1EN | RCC_APB2ENR_IOPAEN;
 // Configure PA9 (TX) as alternate function push-pull
 GPIOA->CRH &= ~GPIO_CRH_MODE9;
 GPIOA->CRH |= GPIO_CRH_MODE9_1; // Output mode, max speed 2 MHz
 GPIOA->CRH &= ~GPIO_CRH_CNF9;
 GPIOA->CRH |= GPIO_CRH_CNF9_1; // Alternate function push-pull
 // Configure PA10 (RX) as input floating
 GPIOA->CRH &= ~GPIO_CRH_MODE10;
 GPIOA->CRH &= ~GPIO_CRH_CNF10;
 GPIOA->CRH |= GPIO_CRH_CNF10_0; // Input floating
 // Configure USART1
 USART1->BRR = 0x1D4C; // Baud rate 9600 (assuming 72 MHz clock)
 USART1->CR1 |= USART_CR1_UE; // Enable USART
 USART1->CR1 |= USART_CR1_TE; //Enable transmitter
 }
 /* UART Send String */
 void UART_SendString(const char *str) {
 while (*str) {
 while (!(USART1->SR & USART_SR_TXE)); // Wait until TXE is set
USART1->DR = *str++;
 // Send character
 }
 }
 /* Simple delay function */
 void delay_ms(uint32_t ms) {
 for (uint32_t i = 0; i < ms * 8000; i++) {
 __NOP();
 }
 }