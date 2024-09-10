#include "main.h"
#include "system.h"
#include "motor.h"
#include "relay.h"
#include "adc.h"
#include "usart.h"

extern ADC_HandleTypeDef hadc1;
extern UART_HandleTypeDef huart1;

uint8_t Flag = 0;
int Pressure = 0;

uint16_t ADC_Value; // ADC值
int Pwm_1 = 1500;	// 中间段pwm
int Pwm_2 = 3000;	// 两端pwm

float Pressure_V = 0.0;
long pressure = 0;

char V_disbuff[5] = {0};
char P_disbuff[6] = {0};

const float VCC = 3300; // ADC参考电压为mV

const float Voltage_0 = 160;   // 零点电压值mV  校准时需修改
const float Voltage_40 = 3750; // 满量程输出电压值mV  需修改

long map(long x, long in_min, long in_max, long out_min, long out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

uint16_t Get_Adc_Average(ADC_HandleTypeDef *hadc, uint8_t times)
{
	uint32_t temp_val = 0;
	uint8_t t;
	for (t = 0; t < times; t++)
	{
		temp_val += HAL_ADC_GetValue(hadc);
		//		delay_ms(5);
	}
	return temp_val / times;
}

float Pressure_Calculate(ADC_HandleTypeDef *hadc, uint8_t times)
{
	uint32_t temp_val = 0;
	float pressure = 0;
	temp_val = Get_Adc_Average(hadc, times);
	pressure = ((float)temp_val - 1810.0) * 5 / 77; // 100kPa的压力传感器
	return pressure;
}

// void BEND_Value_Conversion()
//{
//		/*显示电压值*/
//		V_disbuff[0]=(long int)(Pressure_V)/1000+'0';
//		V_disbuff[1]=(long int)(Pressure_V)%1000/100+'0';
//		V_disbuff[2]=(long int)(Pressure_V)%100/10+'0';
//		V_disbuff[3]=(long int)(Pressure_V)%10+'0';
//	  OLED_ShowStr(36,2,V_disbuff,2);
//
//     /*显示气压值*/
//		if(pressure<=0){pressure=0;}
//		if(pressure>=40000){pressure=40000;}
//
//		P_disbuff[0]=(int)((pressure))/10000+'0';
//		P_disbuff[1]=(int)((pressure))%10000/1000+'0';
//		P_disbuff[2]=(int)((pressure))%1000/100+'0';
//		P_disbuff[3]=(int)((pressure))%100/10+'0';
//		P_disbuff[4]=(int)((pressure))%10+'0';
//		OLED_ShowStr(27,4,P_disbuff,2);
// }

void Test_Li(uint8_t mode)
{
	if (mode == 1)
	{
		Body_MotionStatus(0, 0, 0); // 控制出气吸气
		Body_Status(0, 0, 0, 0, 0, 0);
		while (1)
		{
			Minipump1_MotionStatus(1);
			Minipump1_Status(1, Head_And_Tail_Pump_Strength);
			HAL_Delay(Head_And_Tail_PumpOut_Time_ms);
			Minipump1_Status(0, 0);
			HAL_Delay(Between_Two_Action_Delay_Time_ms);

			Minipump1_MotionStatus(0);
			Minipump1_Status(1, Head_And_Tail_Pump_Strength);
			HAL_Delay(Head_And_Tail_PumpIn_Time_ms);
			Minipump1_Status(0, 0);
			HAL_Delay(Between_Two_Action_Delay_Time_ms);

			Minipump2_MotionStatus(1);
			Minipump2_Status(1, Head_And_Tail_Pump_Strength);
			HAL_Delay(Head_And_Tail_PumpOut_Time_ms);
			Minipump2_Status(0, 0);
			HAL_Delay(Between_Two_Action_Delay_Time_ms);

			Minipump2_MotionStatus(0);
			Minipump2_Status(1, Head_And_Tail_Pump_Strength);
			HAL_Delay(Head_And_Tail_PumpIn_Time_ms);
			Minipump2_Status(0, 0);
			HAL_Delay(Between_Two_Action_Delay_Time_ms);
		}
	}
	else if (mode == 2)
	{
		while (1)
		{
			Body_MotionStatus(0, 1, 1); // 控制出气吸气
			Body_Status(1, Body_Pump_Strength, 1, Body_Pump_Strength, 1, Body_Pump_Strength);
			HAL_Delay(Body_PumpInOrOut_Time_ms);
			Body_Status(0, 0, 0, 0, 0, 0);
			HAL_Delay(Between_Two_Action_Delay_Time_ms);

			Body_MotionStatus(1, 0, 0);
			Body_Status(1, Body_Pump_Strength, 1, Body_Pump_Strength, 1, Body_Pump_Strength);
			HAL_Delay(Body_PumpInOrOut_Time_ms);
			Body_Status(0, 0, 0, 0, 0, 0);
			HAL_Delay(Between_Two_Action_Delay_Time_ms);
		}
	}
	else if (mode == 3)
	{
		// 尾泵固定
		Minipump1_MotionStatus(1);
		Minipump1_Status(1, Head_And_Tail_Pump_Strength);
		HAL_Delay(Head_And_Tail_PumpOut_Time_ms);
		Minipump1_Status(0, 0);
		HAL_Delay(Between_Two_Action_Delay_Time_ms);

		// 头泵松开
		Minipump2_MotionStatus(0);
		Minipump2_Status(1, Head_And_Tail_Pump_Strength);
		HAL_Delay(Head_And_Tail_PumpIn_Time_ms);
		Minipump2_Status(0, 0);
		HAL_Delay(Between_Two_Action_Delay_Time_ms);

		// 身体弯曲
		Body_MotionStatus(0, 1, 1); // 控制出气吸气
		Body_Status(1, Body_Pump_Strength, 1, Body_Pump_Strength, 1, Body_Pump_Strength);
		HAL_Delay(Body_PumpInOrOut_Time_ms);
		Body_Status(0, 0, 0, 0, 0, 0);
		HAL_Delay(Between_Two_Action_Delay_Time_ms);

		// 头泵固定
		Minipump2_MotionStatus(1);
		Minipump2_Status(1, Head_And_Tail_Pump_Strength);
		HAL_Delay(Head_And_Tail_PumpOut_Time_ms);
		Minipump2_Status(0, 0);
		HAL_Delay(Between_Two_Action_Delay_Time_ms);

		// 尾泵松开
		Minipump1_MotionStatus(0);
		Minipump1_Status(1, Head_And_Tail_Pump_Strength);
		HAL_Delay(Head_And_Tail_PumpIn_Time_ms);
		Minipump1_Status(0, 0);
		HAL_Delay(Between_Two_Action_Delay_Time_ms);

		// 身体另一侧弯曲
		Body_MotionStatus(1, 0, 0);
		Body_Status(1, Body_Pump_Strength, 1, Body_Pump_Strength, 1, Body_Pump_Strength);
		HAL_Delay(Body_PumpInOrOut_Time_ms);
		Body_Status(0, 0, 0, 0, 0, 0);
		HAL_Delay(Between_Two_Action_Delay_Time_ms);
	}
	else if (mode == 4)
	{
		while (1)
		{
			// 尾泵固定
			Minipump1_MotionStatus(1);
			Minipump1_Status(1, Head_And_Tail_Pump_Strength);
			HAL_Delay(Head_And_Tail_PumpOut_Time_ms);
			Minipump1_Status(0, 0);
			HAL_Delay(Between_Two_Action_Delay_Time_ms);

			// 头泵松开
			Minipump2_MotionStatus(0);
			Minipump2_Status(1, Head_And_Tail_Pump_Strength);
			HAL_Delay(Head_And_Tail_PumpIn_Time_ms);
			Minipump2_Status(0, 0);
			HAL_Delay(Between_Two_Action_Delay_Time_ms);

			// 身体弯曲
			Body_MotionStatus(0, 1, 1); // 控制出气吸气
			Body_Status(1, Body_Pump_Strength, 1, Body_Pump_Strength, 1, Body_Pump_Strength);
			HAL_Delay(Body_PumpInOrOut_Time_ms);
			Body_Status(0, 0, 0, 0, 0, 0);
			HAL_Delay(Between_Two_Action_Delay_Time_ms);

			// 头泵固定
			Minipump2_MotionStatus(1);
			Minipump2_Status(1, Head_And_Tail_Pump_Strength);
			HAL_Delay(Head_And_Tail_PumpOut_Time_ms);
			Minipump2_Status(0, 0);
			HAL_Delay(Between_Two_Action_Delay_Time_ms);

			// 尾泵松开
			Minipump1_MotionStatus(0);
			Minipump1_Status(1, Head_And_Tail_Pump_Strength);
			HAL_Delay(Head_And_Tail_PumpIn_Time_ms);
			Minipump1_Status(0, 0);
			HAL_Delay(Between_Two_Action_Delay_Time_ms);

			// 身体另一侧弯曲
			Body_MotionStatus(1, 0, 0);
			Body_Status(1, Body_Pump_Strength, 1, Body_Pump_Strength, 1, Body_Pump_Strength);
			HAL_Delay(Body_PumpInOrOut_Time_ms);
			Body_Status(0, 0, 0, 0, 0, 0);
			HAL_Delay(Between_Two_Action_Delay_Time_ms);
		}
	}
	else if (mode == 5)
	{
		Body_MotionStatus(0, 1, 1); // 控制出气吸气
		Body_Status(1, Body_Pump_Strength, 1, Body_Pump_Strength, 1, Body_Pump_Strength);
		HAL_Delay(Body_PumpInOrOut_Time_ms);
		Body_Status(1, body_keep_K * Body_Pump_Strength, 1, body_keep_K * Body_Pump_Strength, 1, body_keep_K * Body_Pump_Strength);
		while (1)
		{
		}
	}
	else if (mode == 6)
	{
		// 尾泵固定
		Minipump1_MotionStatus(1);
		Minipump1_Status(1, Head_And_Tail_Pump_Strength);
		HAL_Delay(Head_And_Tail_PumpOut_Time_ms);
		Minipump1_Status(1, Head_And_Tail_Pump_Strength * head_and_tail_keep_K);
		while (1)
		{
		}
	}
	else if (mode == 7)
	{
		while (1)
		{
			// 尾泵固定
			Minipump1_MotionStatus(1);
			Minipump1_Status(1, Head_And_Tail_Pump_Strength);
			HAL_Delay(Head_And_Tail_PumpOut_Time_ms);
			Minipump1_Status(1, head_and_tail_keep_K * Head_And_Tail_Pump_Strength);
			HAL_Delay(Between_Two_Action_Delay_Time_ms);

			// 头泵松开
			Minipump2_MotionStatus(0);
			Minipump2_Status(1, Head_And_Tail_Pump_Strength);
			HAL_Delay(Head_And_Tail_PumpIn_Time_ms);
			Minipump2_Status(1, head_and_tail_keep_K * Head_And_Tail_Pump_Strength);
			HAL_Delay(Between_Two_Action_Delay_Time_ms);

			// 身体弯曲
			Body_MotionStatus(0, 1, 1); // 控制出气吸气
			Body_Status(1, Body_Pump_Strength, 1, Body_Pump_Strength, 1, Body_Pump_Strength);
			HAL_Delay(Body_PumpInOrOut_Time_ms);
			Body_Status(1, body_keep_K * Body_Pump_Strength, 1, body_keep_K * Body_Pump_Strength, 1, body_keep_K * Body_Pump_Strength);
			HAL_Delay(Between_Two_Action_Delay_Time_ms);

			// 头泵固定
			Minipump2_MotionStatus(1);
			Minipump2_Status(1, Head_And_Tail_Pump_Strength);
			HAL_Delay(Head_And_Tail_PumpOut_Time_ms);
			Minipump2_Status(1, head_and_tail_keep_K * Head_And_Tail_Pump_Strength);
			HAL_Delay(Between_Two_Action_Delay_Time_ms);

			// 尾泵松开
			Minipump1_MotionStatus(0);
			Minipump1_Status(1, Head_And_Tail_Pump_Strength);
			HAL_Delay(Head_And_Tail_PumpIn_Time_ms);
			Minipump1_Status(1, head_and_tail_keep_K * Head_And_Tail_Pump_Strength);
			HAL_Delay(Between_Two_Action_Delay_Time_ms);

			// 身体另一侧弯曲
			Body_MotionStatus(1, 0, 0);
			Body_Status(1, Body_Pump_Strength, 1, Body_Pump_Strength, 1, Body_Pump_Strength);
			HAL_Delay(Body_PumpInOrOut_Time_ms);
			Body_Status(1, body_keep_K * Body_Pump_Strength, 1, body_keep_K * Body_Pump_Strength, 1, body_keep_K * Body_Pump_Strength);
			HAL_Delay(Between_Two_Action_Delay_Time_ms);
		}
	}
}

void Run_on_off(uint8_t mode)
{
	if (mode == 1)
	{
		//		Body_MotionStatus(0,1,1);     //控制出气吸气
		//		Body_Status(1,1500,1,1500,1,1500);
		//		HAL_Delay(Body_PumpInOrOut_Time_ms);
		//		Body_Status(0,0,0,0,0,0);
		//		HAL_Delay(Between_Two_Action_Delay_Time_ms);
		//
		//		Body_MotionStatus(1,0,0);
		//		Body_Status(1,1500,1,1500,1,1500);
		//		HAL_Delay(Body_PumpInOrOut_Time_ms);
		//		Body_Status(0,0,0,0,0,0);
		//		HAL_Delay(Between_Two_Action_Delay_Time_ms);

		Minipump1_MotionStatus(1);
		Minipump1_Status(1, 3500);
		HAL_Delay(Head_And_Tail_PumpOut_Time_ms);
		Minipump1_Status(0, 0);
		HAL_Delay(Between_Two_Action_Delay_Time_ms);

		Minipump1_MotionStatus(0);
		Minipump1_Status(1, 3500);
		HAL_Delay(Head_And_Tail_PumpIn_Time_ms);
		Minipump1_Status(0, 0);
		HAL_Delay(Between_Two_Action_Delay_Time_ms);

		Minipump2_MotionStatus(1);
		Minipump2_Status(1, 3500);
		HAL_Delay(Head_And_Tail_PumpOut_Time_ms);
		Minipump2_Status(0, 0);
		HAL_Delay(Between_Two_Action_Delay_Time_ms);

		Minipump2_MotionStatus(0);
		Minipump2_Status(1, 3500);
		HAL_Delay(Head_And_Tail_PumpIn_Time_ms);
		Minipump2_Status(0, 0);
		HAL_Delay(Between_Two_Action_Delay_Time_ms);
	}
	else if (mode == 0)
	{
		//		Body_Status(0,0,0,0,0,0);
		//		Minipump1_Status(0,0);
		Minipump2_Status(0, 0);
		Minipump1_Status(0, 0);
	}
	else if (mode == 2)
	{
	}
}

void Run(uint8_t mode)
{
	HAL_ADC_Start(&hadc1);				   // 启动ADC转换
	HAL_ADC_PollForConversion(&hadc1, 50); // 等待转换完成，50为最大等待时间，单位为ms

	if (HAL_IS_BIT_SET(HAL_ADC_GetState(&hadc1), HAL_ADC_STATE_REG_EOC))
	{
		Pressure = Pressure_Calculate(&hadc1, 5);
		HAL_UART_Transmit(&huart1, (uint8_t *)&Pressure, sizeof(Pressure), 0xFFFF);
	}
	/*********************************************************/

	static int Flag = 1;
	if (mode == 0)
	{
		Minipump1_Status(0, 0);
		Minipump2_Status(0, 0);
		Body_Status(0, 0, 0, 0, 0, 0);
	}
	else if (mode == 1)
	{
		if (Flag == 1)
		{
			Minipump1_MotionStatus(1); // 小1出气吸附
			Minipump1_Status(1, Pwm_2);
			HAL_Delay(Head_And_Tail_PumpOut_Time_ms);
			Minipump1_Status(0, 0);
			HAL_Delay(Between_Two_Action_Delay_Time_ms);

			Flag = 0;
		}
		Body_MotionStatus(0, 1, 1); // 大1收缩 大2大3伸展
		Body_Status(1, Pwm_1, 1, Pwm_1, 1, 1700);
		HAL_Delay(Body_PumpInOrOut_Time_ms);
		Body_Status(0, 0, 0, 0, 0, 0);
		HAL_Delay(Between_Two_Action_Delay_Time_ms);

		Minipump2_MotionStatus(1); // 小2出气吸附
		Minipump2_Status(1, Pwm_2);
		HAL_Delay(Head_And_Tail_PumpOut_Time_ms);
		Minipump2_Status(0, 0);
		HAL_Delay(Between_Two_Action_Delay_Time_ms);

		Minipump1_MotionStatus(0); // 小1吸气脱离
		Minipump1_Status(1, Pwm_2);
		HAL_Delay(Head_And_Tail_PumpIn_Time_ms);
		Minipump1_Status(0, 0);
		HAL_Delay(Between_Two_Action_Delay_Time_ms);

		Body_MotionStatus(1, 0, 0); // 大1伸展  大2大3收缩
		Body_Status(1, Pwm_1, 1, Pwm_1, 1, Pwm_1);
		HAL_Delay(Body_PumpInOrOut_Time_ms);
		Body_Status(0, 0, 0, 0, 0, 0);
		HAL_Delay(Between_Two_Action_Delay_Time_ms);

		Minipump1_MotionStatus(1); // 小1出气吸附
		Minipump1_Status(1, Pwm_2);
		HAL_Delay(Head_And_Tail_PumpOut_Time_ms);
		Minipump1_Status(0, 0);
		HAL_Delay(Between_Two_Action_Delay_Time_ms);

		Minipump2_MotionStatus(0); // 小2吸气脱离
		Minipump2_Status(1, Pwm_2);
		HAL_Delay(Head_And_Tail_PumpIn_Time_ms);
		Minipump2_Status(0, 0);
		HAL_Delay(Between_Two_Action_Delay_Time_ms);
	}
}

void Test(uint8_t mode)
{
	int num = 13;
	HAL_UART_Transmit(&huart1, (uint8_t *)&num, sizeof(num), 0xFFFF);
}
