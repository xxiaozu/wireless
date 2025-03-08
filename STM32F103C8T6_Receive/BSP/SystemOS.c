#include "SystemOS.h"




void SystemOS_Init()
{
	HAL_TIM_Base_Start_IT(&htim2);
	NRF_Dev_Init();
	
}
/**************************************************************************
*	MouseBuf[0]--
*	|--bit7~bit3: 
*	|--bit2:   1��ʾ�м�����
*	|--bit1:   1��ʾ�Ҽ�����
*	|--bit0:   1��ʾ�������
*
*	MouseBuf[1]-- X����仯����������ʾ�����ƣ����������ơ��ò����ʾ�仯��
*	MouseBuf[2]-- Y����仯����������ʾ�����ƣ����������ơ��ò����ʾ�仯��
*	MouseBuf[3]-- ���ֱ仯,������ʾ���Ϲ�����������ʾ���¹���
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
			memset(MouseBuf, 0, 4);//�����������
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



