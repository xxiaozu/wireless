#include "SystemOS.h"




uint16_t _10ms_time = 0, sec = 0;
uint16_t ADC_Value[2];
short GyroRawStaticError[3] = {0};

void SystemOS_Init()
{
	
	MPU_Init();
	
	HAL_ADC_Start_DMA(&hadc1,(uint32_t*)&ADC_Value,2);
	
	HAL_TIM_Base_Start_IT(&htim2);
	
	NRF_Dev_Init();
	
}
/**************************************************************************
*	MouseBuf[0]--
*	|--bit7~bit3: 
*	|--bit2:   1表示中键按下
*	|--bit1:   1表示右键按下
*	|--bit0:   1表示左键按下
*
*	MouseBuf[1]-- X坐标变化量，负数表示向左移，正数表右移。用补码表示变化量
*	MouseBuf[2]-- Y坐标变化量，负数表示向下移，正数表上移。用补码表示变化量
*	MouseBuf[3]-- 滚轮变化,负数表示向上滚动，负数表示向下滚动
***************************************************************************/
short gyrox,gyroy,gyroz;		//陀螺仪原始数据
void SystemOS_Loop()
{
	MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);

	NRF_TX_Buff[1] = -(uint8_t)((ADC_Value[0] - 2048)/128) - gyroz/64;
	NRF_TX_Buff[2] =  (uint8_t)((ADC_Value[1] - 2048)/128) - gyrox/64;

	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_RESET)
	{
		HAL_Delay(15);
		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_RESET)
		{
			NRF_TX_Buff[0] |= 0x01;
		}
	}
	else
	{
		NRF_TX_Buff[0] &= 0xFE;
	}
	
	NRF_Send_Packet(NRF_TX_Buff);
		
	if(NRF_TX_Buff[0] || NRF_TX_Buff[1] || NRF_TX_Buff[2] || NRF_TX_Buff[3])
	{
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13, GPIO_PIN_RESET);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13, GPIO_PIN_SET);
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	
    if (htim == (&htim2))//10ms
    {
		_10ms_time++;
		if(_10ms_time%100 == 0)
		{
			sec++;
		}
    }
}



