#include "stm32f10x.h" // Include CMSIS library for STM32F1

/* Function Prototypes */
void SystemClock_Config(void);
void GPIO_Init(void);
void TIM2_Init(void);

/* Main Function */
int main(void) {
    /* Configure System Clock */
    SystemClock_Config();

    /* Initialize GPIO and Timer */
    GPIO_Init();
    TIM2_Init();

    /* Start Timer2 */
    TIM2->CR1 |= TIM_CR1_CEN; // Enable Timer2

    /* Infinite loop */
    while (1) {
        // Wait for Timer2 overflow
        if (TIM2->SR & TIM_SR_UIF) { // Check update interrupt flag (UIF)
            TIM2->SR &= ~TIM_SR_UIF; // Clear UIF flag

            // Toggle LED on PC13
            GPIOC->ODR ^= GPIO_ODR_ODR13;
        }
    }
}

/* System Clock Configuration */
void SystemClock_Config(void) {
    RCC->CR |= RCC_CR_HSION; // Enable HSI
    while (!(RCC->CR & RCC_CR_HSIRDY)); // Wait until HSI is ready

    RCC->CFGR &= ~RCC_CFGR_SW;      // Clear SW bits
    RCC->CFGR |= RCC_CFGR_SW_HSI;   // Select HSI as system clock
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI); // Wait for HSI
}


/* GPIO Initialization */
void GPIO_Init(void) {
    /* Enable GPIOC Clock */
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;

    /* Configure PC13 as output for LED */
    GPIOC->CRH &= ~GPIO_CRH_MODE13; // Clear mode
    GPIOC->CRH |= GPIO_CRH_MODE13_0; // Output mode 2 MHz
    GPIOC->CRH &= ~GPIO_CRH_CNF13; // Push-pull
}

/* Timer2 Initialization */
void TIM2_Init(void) {
    /* Enable Timer2 Clock */
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    /* Configure Timer2 */
    TIM2->PSC = 999;
    TIM2->ARR = 8000-1;
    TIM2->CR1 |= TIM_CR1_ARPE; // Enable auto-reload preload
}