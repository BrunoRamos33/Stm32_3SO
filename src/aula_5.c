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

void aula_5_GPIO_Init(void)
{
	//Enable GPIO Clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure_TX;
	GPIO_InitTypeDef GPIO_InitStructure_RX;
	//GPIO cfg for TX
	GPIO_InitStructure_TX.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure_TX.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure_TX.GPIO_Mode = GPIO_Mode_AF_PP;
	//GPIO cfg for Bottom
	GPIO_InitStructure_RX.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure_RX.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure_RX.GPIO_Mode = GPIO_Mode_IN_FLOATING;

	GPIO_Init(GPIOA, &GPIO_InitStructure_TX);
	GPIO_Init(GPIOA, &GPIO_InitStructure_RX);
	return;
}

void aula_5_USART_Init(void)
{
	//Variable declaration
	USART_InitTypeDef USART_InitStructure;

	//Enable USART Clock
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	//USART CFG
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_Odd;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

	//USART INIT
	USART_Init(USART2, &USART_InitStructure);
	//USART ENABLE
	USART_Cmd(USART2, ENABLE);
	return;
}

void aula_5_Send_Hello(void)
{
	/*Enviar os dados – neste caso carácter é o 'a'*/
	USART_SendData(USART2, 'a');
	/*Esperar que o buffer esteja vazio*/
	while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
	return;
}
