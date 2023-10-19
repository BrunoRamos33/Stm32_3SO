#include "stm32f10x_gpio.h"
#define DELAY_DEFAULT	1000
static void delay(uint32_t milliseconds)
{
    // Calculate the number of loop iterations based on your clock frequency
    // For example, if your clock frequency is 1 MHz, you can use 1000 loops to create a 1 ms delay.
    // Adjust this value based on your specific microcontroller and clock speed.
    uint32_t loop_count = milliseconds * 1000;
    // Dummy loop for the delay
    for (uint32_t i = 0; i < loop_count; i++) {
        // This loop will take time, and it can be used to create a delay
        // The actual time delay depends on your microcontroller's clock frequency
    }
    return;
}

void aula_1_Init(void)
{
	//Enable GPIO Clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure_Led;
	GPIO_InitTypeDef GPIO_InitStructure_Bottom;
	//GPIO cfg for LED
	GPIO_InitStructure_Led.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure_Led.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure_Led.GPIO_Mode = GPIO_Mode_Out_PP;
	//GPIO cfg for Bottom
	GPIO_InitStructure_Bottom.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure_Bottom.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure_Bottom.GPIO_Mode = GPIO_Mode_IN_FLOATING;

	GPIO_Init(GPIOA, &GPIO_InitStructure_Led);
	GPIO_Init(GPIOC, &GPIO_InitStructure_Bottom);
	return;
}

void aula_2_Action(void)
{
	static uint32_t DelayInMiliseconds = DELAY_DEFAULT;//1 second delay
	if (GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13))
		DelayInMiliseconds = DELAY_DEFAULT;
	else
		DelayInMiliseconds = DELAY_DEFAULT/2;

	GPIO_SetBits( GPIOA, GPIO_Pin_5);
	delay(DelayInMiliseconds);
	GPIO_ResetBits( GPIOA, GPIO_Pin_5);
	delay(DelayInMiliseconds);
	return;
}
