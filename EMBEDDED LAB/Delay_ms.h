#include "stm32f10x.h"                  // Device header

void TIM2Config (void)
{
		/************** STEPS TO FOLLOW *****************
	1. Enable Timer clock
	2. Set the prescalar and the ARR
	3. Enable the Timer, and wait for the update Flag to set
	************************************************/
	
// - TIM2CLK ENABLE - // 
    RCC->CR|= RCC_CR_PLLON; 
 
    // - Auto Reload Register (ARR) - // This is a 16 bit register, so the maximum value can be 0xffff 
    TIM2->ARR = 0xffff-1; 
    //SET UP PRESCALER//  
    TIM2->PSC = 72-1; //--us/ 
    //enable timer// 
    TIM2->CR1 |= (1<<0); 
    //Enable update flag// 
    while(!(TIM2->SR & (1<<0))); //wait to set// 
}

void delay_us (uint16_t us)
{
	/************** STEPS TO FOLLOW *****************
	1. RESET the Counter
	2. Wait for the Counter to reach the entered value. As each count will take 1 us, 
		 the total waiting time will be the required us delay
	************************************************/
	
	TIM2->CNT &= ~(0xffff);
	while(TIM2->CNT < us);
}

void delay_ms (uint16_t ms)
{
	for(uint16_t i=0;i<ms;i++)
	{
		delay_us(1000); // 1 ms delay
	}
}
