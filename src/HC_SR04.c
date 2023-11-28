//Driver for HC_SR04

#include "stm32f10x_gpio.h"
#include "time_measurement.h"

static void delay(uint32_t microseconds)
{
    // Calculate the number of loop iterations based on your clock frequency
    // For example, if your clock frequency is 72 MHz, you can use 72 loops to create a 1 us delay.
    // Adjust this value based on your specific microcontroller and clock speed.
    uint32_t loop_count = microseconds * 72;
        // Dummy loop for the delay
    for (uint32_t i = 0; i < loop_count; i++) {
        // This loop will take time, and it can be used to create a delay
        // The actual time delay depends on your microcontroller's clock frequency
    }
    return;
}

void HC_SR04_Init(void)
{
	//Enable GPIO Clock
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure_Trigger;
	GPIO_InitTypeDef GPIO_InitStructure_Echo;
	//GPIO cfg - Trigger
	GPIO_InitStructure_Trigger.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure_Trigger.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure_Trigger.GPIO_Mode = GPIO_Mode_Out_PP;
	//GPIO cfg - echo
	GPIO_InitStructure_Echo.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure_Echo.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure_Echo.GPIO_Mode = GPIO_Mode_IN_FLOATING;

	GPIO_Init(GPIOA, &GPIO_InitStructure_Trigger);
	GPIO_Init(GPIOA, &GPIO_InitStructure_Echo);

	return;
}

uint32_t HC_SR04_Get_Distance(void)
{
	uint32_t DelayInMicroseconds = 0x1;
	uint32_t rtn_value = 0x00;
	uint16_t time_elaped = 0x00;

	GPIOA->BSRR = GPIO_Pin_8;
	delay(DelayInMicroseconds);
	GPIOA->BRR = GPIO_Pin_8;

	//Wait for the echo pin to go high
	while(!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_9));
	//start Timer
	time_measurement_start_measurement();

	//wait for echo pin to go low
	while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_9));
	//get time elapsed
	time_elaped = time_measurement_get_time();

	//Speed of sound is 343 m/s, 58us/cm ,so distance = time * speed / 2
	//discance in cm
	rtn_value = (uint32_t)((uint32_t)time_elaped / (58UL));
	return rtn_value;
}
