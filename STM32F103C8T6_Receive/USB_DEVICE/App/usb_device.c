/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : usb_device.c
  * @version        : v2.0_Cube
  * @brief          : This file implements the USB Device
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/

#include "usb_device.h"
#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_hid.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USB Device Core handle declaration. */
USBD_HandleTypeDef hUsbDeviceFS;

/*
 * -- Insert your variables declaration here --
 */
/* USER CODE BEGIN 0 */

uint8_t MouseBuf[4] = {0, 0, 0, 0};

/**************************************************************************
*	Mouse_Buffer[0]--
*	|--bit7~bit3: 
*	|--bit2:   1��ʾ�м�����
*	|--bit1:   1��ʾ�Ҽ�����
*	|--bit0:   1��ʾ�������
*
*	Mouse_Buffer[1]-- X����仯����������ʾ�����ƣ����������ơ��ò����ʾ�仯��
*	Mouse_Buffer[2]-- Y����仯����������ʾ�����ƣ����������ơ��ò����ʾ�仯��
*	Mouse_Buffer[3]-- ���ֱ仯,������ʾ���Ϲ�����������ʾ���¹���
***************************************************************************/
void MouseMove(int8_t x,int8_t y)
{
	MouseBuf[1] = x;
	MouseBuf[2] = y;
}

void MouseLeftPress()
{
	MouseBuf[0] |= 0x01;//������
}

void MouseLeftUnpress()
{
	MouseBuf[0] &= 0xFE;//����ͷ�
}

void MouseRightPress()
{
	MouseBuf[0] |= 0x02;//�Ҽ����
}

void MouseRightUnpress()
{
	MouseBuf[0] &= 0xFD;//�Ҽ��ͷ�
}

void MouseUpdate()
{
	USBD_HID_SendReport(&hUsbDeviceFS, MouseBuf, 4);
}
/* USER CODE END 0 */

/*
 * -- Insert your external function declaration here --
 */
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/**
  * Init USB device Library, add supported class and start the library
  * @retval None
  */
void MX_USB_DEVICE_Init(void)
{
  /* USER CODE BEGIN USB_DEVICE_Init_PreTreatment */

  /* USER CODE END USB_DEVICE_Init_PreTreatment */

  /* Init Device Library, add supported class and start the library. */
  if (USBD_Init(&hUsbDeviceFS, &FS_Desc, DEVICE_FS) != USBD_OK)
  {
    Error_Handler();
  }
  if (USBD_RegisterClass(&hUsbDeviceFS, &USBD_HID) != USBD_OK)
  {
    Error_Handler();
  }
  if (USBD_Start(&hUsbDeviceFS) != USBD_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN USB_DEVICE_Init_PostTreatment */

  /* USER CODE END USB_DEVICE_Init_PostTreatment */
}

/**
  * @}
  */

/**
  * @}
  */

