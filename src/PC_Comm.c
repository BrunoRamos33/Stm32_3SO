#include "USART.h"
#include <stdio.h>
#include "time_measurement.h"

static void delay(uint32_t microseconds)
{
    // Calculate the number of loop iterations based on your clock frequency
    // For example, if your clock frequency is 72 MHz, you can use 72 loops to create a 1 ms delay.
    // Adjust this value based on your specific microcontroller and clock speed.
    uint32_t loop_count = microseconds * 72;
    // Dummy loop for the delay
    for (uint32_t i = 0; i < loop_count; i++) {
        // This loop will take time, and it can be used to create a delay
        // The actual time delay depends on your microcontroller's clock frequency
    }
    return;
}

void responder(char s[], char c)
{
	char sComm[11];
	unsigned char i = 5, j = 0;
	while( (s[i] != '\0') && (j <= 11) )
	{
		if( (s[i] >= '0') && (s[i] <= '9') )
		{
			sComm[j++] = s[i++];
		}
		else
		{
			USART_2_sendString("Error - Comm");
			USART_2_sendChar(c);
			USART_2_sendString(" received a non integer: ");
			USART_2_sendChar(s[i]);
			USART_2_sendChar('\r');
		}
	}

	sComm[j] = '\0';

	if(j>11)
	{
		USART_2_sendString("Error - Comm");
		USART_2_sendChar(c);
		USART_2_sendString(" number too large\r");
		USART_2_sendChar('\r');
	}else
	{
		USART_2_sendString("\rThank you for sending the number: ");
		USART_2_sendString(sComm);
		USART_2_sendChar('\r');
	}

}


void Comm1(char s[])
{
	char str[6];
	uint16_t time_in_ms = 0x00;
	time_measurement_start_measurement();
	//delay
	delay(1);
	time_in_ms = time_measurement_get_time();
	sprintf(str,"%d",time_in_ms);
	USART_2_sendString("\rTimeMeasurement POC = ");
	USART_2_sendString(str);
	USART_2_sendString("us");
	USART_2_sendChar('\r');
}

void Comm2(char s[])
{
	responder(s,s[4]);
}

void Comm3(char s[])
{
	responder(s,s[4]);
}

void Comm4(char s[])
{
	responder(s,s[4]);
}

void PC_Comm_parseInput(char s[])
{
	// parse first character
	switch (s[0])
	{

		case 'c':
			if( (s[1] == 'o') && (s[2] == 'm') && (s[3] == 'm') )
				switch (s[4]) // parse the fifth character
				{
					case 'a':
						Comm1(s);
						break;
					case 'b':
						Comm2(s);
						break;
					case 'c':
						Comm3(s);
						break;
					case 'd':
						Comm4(s);
						break;
					default:
						USART_2_sendString("\rYou sent: '");
						USART_2_sendChar(s[0]);
						USART_2_sendString("' - I don't understand.\r");
				}
			break;
		case 'd':
			if( (s[1] == 'e') && (s[2] == 'm') && (s[3] == 'o') && (s[4] == '?') )
				USART_2_sendString("You are talking to the PC_Comm demo.\r");
			break;
		case 'h':
			if( (s[1] == 'e') && (s[2] == 'l') && (s[3] == 'l') && (s[4] == 'o') )
				USART_2_sendString("Hello yourself\r");
			break;
		default:
			USART_2_sendString("\rYou sent: '"); USART_2_sendChar(s[0]);
			USART_2_sendString("' - I don't understand.\r"); break;
	}
	s[0] = '\0';
}
