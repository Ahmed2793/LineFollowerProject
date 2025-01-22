#include "stm32f10x.h"
 void initClockPLL(void);
 void initClockHSI(void);
 void initClockHSE(void);
 void delayMicroseconds(uint32_t value);
 void initTIM1(void);
 void initSysTick(uint32_t value);
 void initGPIO(void);
 int main() {
 // Initialize the clock to use PLL as the system clock
 initClockHSI();
 initSysTick(800);
 initTIM1();
 initGPIO();
 // Duty Cycle
 TIM1->CCR1 = 1;
 }
 // Function to introduce a delay
 void delayMicroseconds(uint32_t value) {
 while (value > 0) {
 while ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) != SysTick_CTRL_COUNTFLAG); // Wait
 until COUNTFLAG is 1
 value--;
 }
 }
 /**
 * @brief Initializes the clock to use 8MHz HSI as the system clock.
 */
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
 // TIM1 configuration (PWM)
 TIM1->PSC = 8- 1; // Set prescaler to achieve a 1MHz timer clock
 TIM1->ARR = 100; //Set auto-reload value for a 100us period
 TIM1->CCMR1 |= TIM_CCMR1_OC1M_2 |TIM_CCMR1_OC1M_1 |TIM_CCMR1_OC1PE;// PWM
 mode 1,enable preload
 TIM1->CCER |= TIM_CCER_CC1NE; // Enable the capture/compare channel 1 complementary
 output
 TIM1->BDTR |= TIM_BDTR_MOE; // Enable the main output
 TIM1->CR1 |= TIM_CR1_CMS_0 | TIM_CR1_CEN; // Enable TIM1 in center-aligned mode
 TIM1->EGR |= TIM_EGR_UG; // Force update generation
 }
 void initSysTick(uint32_t value) {
 SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk; // Disable SysTick
 SysTick->LOAD = value; // Set reload value
 SysTick->VAL = 0; // Clear current value
 SysTick->CTRL &= ~SysTick_CTRL_CLKSOURCE_Msk; // Configure clock source AHB/8
 SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk; // Disable interrupt
 SysTick->CTRL |= SysTick_CTRL_ENABLE; // Enable SysTick
 }
 void initGPIO(void) {
 // GPIO configuration
 AFIO->MAPR |= AFIO_MAPR_TIM1_REMAP; // Full remap
 RCC->APB2ENR |= RCC_APB2ENR_IOPEEN; // Enable Port E clock
 RCC->APB2ENR |= RCC_APB2ENR_IOPDEN;
 // Configure PE8 for TIMCH1N
 GPIOE->CRH |= GPIO_CRH_MODE8; // Output mode
 GPIOE->CRH &= ~(GPIO_CRH_CNF8); // Alternate output push-pull
 GPIOE->CRH |= GPIO_CRH_CNF8_1;
 }