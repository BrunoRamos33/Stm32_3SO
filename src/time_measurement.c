
#include "stm32f10x_tim.h"
#include "time_measurement.h"

void time_measurement_init(void)
{

	//Enable TIM3 Clock
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	//info: sistr3 page 14
	//TIM struct CFG variable
	//T=((PSC+1)/CK_INT)*(ARR+1)
	//CK_INT = TIM3 Clock Freq. = 36MHz because it belongs to APB1
	//neads to handle values between 150 µs(min) to 38 ms(sensor time out)
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	//TIM 3 CFG
	TIM_TimeBaseStructure.TIM_Period = 38999; //38999dec
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_Prescaler = 71; //35dec
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	//TIM3 Init
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

return;
}

void time_measurement_start_measurement(void)
{
	//Enable TIM3
	TIM_Cmd(TIM3, ENABLE);
	return;
}

uint16_t time_measurement_get_time(void)
{
	uint16_t rtn_value = 0x00U;
	rtn_value = TIM_GetCounter(TIM3);

	//Disable TIM3
	TIM_Cmd(TIM3, DISABLE);
	//Clear Counter register
	TIM_SetCounter(TIM3,0x00U);

	return rtn_value;
}
