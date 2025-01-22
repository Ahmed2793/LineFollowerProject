 #include "stm32f10x.h"
 void initClockHSI(void);
 void initTIM1(void);
 void initGPIO(void);
 int main() {
 // Initialize the system clock and peripherals
 initClockHSI();
 initTIM1();
 initGPIO();
 // Enable the timer to start generating the square wave
 TIM1->CR1 |= TIM_CR1_CEN; // Enable TIM1
 }
 void initClockHSI(void) {
 RCC->CR |= RCC_CR_HSION; // Enable internal HSI (RC)
 while ((RCC->CR & RCC_CR_HSIRDY) != RCC_CR_HSIRDY); // Wait for HSI to be ready
 RCC->CFGR &= ~(RCC_CFGR_SW); // Clear SW bits
 RCC->CFGR |= RCC_CFGR_SW_HSI; // Set HSI as the system clock
while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI); // Wait for HSI to be the system
 clock
 RCC->APB2ENR |= RCC_APB2ENR_TIM1EN; // Enable TIM1 clock
 RCC->APB2ENR |= RCC_APB2ENR_AFIOEN; // Enable alternate function clock
 }
 void initTIM1(void) {
 // Set the timer prescaler to achieve a timer frequency of 1 MHz (1 us per tick)
 TIM1->PSC = 8- 1; // Prescaler value (assuming HSI clock is 8 MHz)
 // Set the auto-reload value to generate a 1 kHz signal (1 ms period)
 TIM1->ARR = 1000- 1; // 1 kHz frequency (period = 1000 ticks at 1 MHz)
 // Configure the timer in PWM mode (toggle output on compare match)
 TIM1->CCMR1 |= TIM_CCMR1_OC1M_2 |TIM_CCMR1_OC1M_1 |TIM_CCMR1_OC1PE;// PWM
 mode 1,preload enable
 TIM1->CCER |= TIM_CCER_CC1E; // Enable the capture/compare channel 1 output
 TIM1->BDTR |= TIM_BDTR_MOE; // Enable the main output
 }
 void initGPIO(void) {
 // GPIO configuration for PE8 (connected to TIM1 CH1)
 RCC->APB2ENR |= RCC_APB2ENR_IOPEEN; // Enable Port E clock
 // Configure PE8 as an alternate function output (PWM output)
 GPIOE->CRH &= ~GPIO_CRH_CNF8; // Reset CNF8
 GPIOE->CRH |= GPIO_CRH_CNF8_1; // Alternate function push-pull
 GPIOE->CRH |= GPIO_CRH_MODE8; // Output mode (maximum speed 50 MHz)
 }