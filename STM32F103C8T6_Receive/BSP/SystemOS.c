#include "SystemOS.h"




void SystemOS_Init()
{
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
uint16_t LossFlag = 0;
uint16_t LossTime = 0;
void SystemOS_Loop()
{
	if(NRF_Rece_Packet(MouseBuf))
	{
		LossFlag = 0;
		LossTime = 0;
		MouseUpdate();
//		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_12);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
	}
	else
	{
		LossFlag = 1;
		
		if(LossTime >= 500)
		{
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
			memset(MouseBuf, 0, 4);//清空数组内容
			MouseUpdate();
			LossTime = 0;
		}
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim == (&htim2))//1ms
    {
		if(LossFlag == 1)
		{
			LossTime++;
		}
    }
}



