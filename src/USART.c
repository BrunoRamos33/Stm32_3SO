//Aula 5
#include "stm32f10x_gpio.h"
#include "string.h"
#define DELAY_DEFAULT	1000


void USART_2_GPIO_Init(void)
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

void USART_2_Init(void)
{
	//Variable declaration
	USART_InitTypeDef USART_InitStructure;

	//Enable USART Clock
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	//USART CFG
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

	//USART INIT
	USART_Init(USART2, &USART_InitStructure);
	//USART ENABLE
	USART_Cmd(USART2, ENABLE);
	return;
}

void USART_2_Send_Hello(void)
{
	/*Esperar que o buffer esteja vazio*/
	while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
	/*Enviar os dados – neste caso carácter é o 'a'*/
	USART_SendData(USART2, 'U');	/*Esperar que o buffer esteja vazio*/
	return;
}

char USART_2_isCharAvailable()
{
	//indicate a char has been received?
	if ( USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == SET )
		return 1; 
	else 
		return 0;
}

char USART_2_receiveChar()
{
	char RxData = '\0';
	/*Ler os dados da USART*/
	RxData = (char)USART_ReceiveData(USART2);
	/*Limpar a flag*/
	USART_ClearFlag(USART2,USART_FLAG_RXNE);

	return RxData;
}

void USART_2_sendChar(char data)
{
	int i = 0;

	//To send data with the USART put the data in the USART data register
	/*Enviar os dados – neste caso carácter é o 'a'*/
	USART_SendData(USART2, (uint8_t)data);
	/*Esperar que o buffer esteja vazio*/
	while((USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET ) && (i<10000))
	{
		i++;
	}
}

void USART_2_sendString(char s[])
{
	int i = 0;	
	while(i < 64) // don't get stuck if it is a bad string
	{
		if( s[i] == '\0' ) break; // quit on string terminator 
			USART_2_sendChar(s[i++]);
	}
}
