#include "main.h"
#include "motor.h"
#include "tim.h"

/**
 * @brief  身体弯曲控制
 * @param  status1: 1:正转 0:停止
 * @param  duty1: 占空比
 */
void Body_Status(uint8_t status1,int duty1,uint8_t status2,int duty2,uint8_t status3,int duty3)    
{
	if(status1 == 0)
	{
		HAL_GPIO_WritePin(IN2_1_GPIO_Port,IN2_1_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(IN2_2_GPIO_Port,IN2_2_Pin,GPIO_PIN_RESET);
	}
	else if(status1 == 1)   //正转
	{
		HAL_GPIO_WritePin(IN2_1_GPIO_Port,IN2_1_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(IN2_2_GPIO_Port,IN2_2_Pin,GPIO_PIN_RESET);

		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, duty1);
	}
	
	if(status2 == 0)
	{
		HAL_GPIO_WritePin(IN3_3_GPIO_Port,IN3_3_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(IN3_4_GPIO_Port,IN3_4_Pin,GPIO_PIN_RESET);
	}
	else if(status2 == 1)
	{
		HAL_GPIO_WritePin(IN3_3_GPIO_Port,IN3_3_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(IN3_4_GPIO_Port,IN3_4_Pin,GPIO_PIN_RESET);
		
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, duty2);
	}
	
		if(status3 == 0)
	{
		HAL_GPIO_WritePin(IN3_1_GPIO_Port,IN3_1_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(IN3_2_GPIO_Port,IN3_2_Pin,GPIO_PIN_RESET);
	}
	else if(status3 == 1)
	{
		HAL_GPIO_WritePin(IN3_1_GPIO_Port,IN3_1_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(IN3_2_GPIO_Port,IN3_2_Pin,GPIO_PIN_RESET);
		
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, duty3);
	}

}

/**
 * @brief  头泵控制
 * @param  status: 1:开启 0:停止
 * @param  duty: 占空比
 */
void Minipump1_Status(uint8_t status,int duty)
{
		if(status == 0)
		{
			HAL_GPIO_WritePin(IN1_1_GPIO_Port,IN1_1_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(IN1_2_GPIO_Port,IN1_2_Pin,GPIO_PIN_RESET);
		}
		else if(status == 1)
		{
			HAL_GPIO_WritePin(IN1_1_GPIO_Port,IN1_1_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(IN1_2_GPIO_Port,IN1_2_Pin,GPIO_PIN_RESET);
			
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, duty);
		}

}

/**
 * @brief  尾泵控制
 * @param  status: 1:开启 0:停止
 * @param  duty: 占空比
 */
void Minipump2_Status(uint8_t status,int duty)
{
		if(status == 0)
		{
			HAL_GPIO_WritePin(IN1_3_GPIO_Port,IN1_3_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(IN1_4_GPIO_Port,IN1_4_Pin,GPIO_PIN_RESET);
		}
		else if(status == 1)
		{
			HAL_GPIO_WritePin(IN1_3_GPIO_Port,IN1_3_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(IN1_4_GPIO_Port,IN1_4_Pin,GPIO_PIN_RESET);
			
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, duty);
		}

}
