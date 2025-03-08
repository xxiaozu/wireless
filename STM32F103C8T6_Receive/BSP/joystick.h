#ifndef __JOYSTICK_H__
#define __JOYSTICK_H__
/*
//#include <iostream>
#include "SystemOS.h"


//#define
					
#define 	LED1_GPIO 				GPIOB,GPIO_PIN_0
#define 	LED2_GPIO 				GPIOB,GPIO_PIN_1
#define 	LED3_GPIO 				GPIOB,GPIO_PIN_10
#define 	LED4_GPIO 				GPIOB,GPIO_PIN_11

#define 	BTN1_GPIO 				GPIOB,GPIO_PIN_12
#define 	BTN2_GPIO 				GPIOB,GPIO_PIN_13
#define 	BTN3_GPIO 				GPIOB,GPIO_PIN_14
#define 	BTN4_GPIO 				GPIOB,GPIO_PIN_15
#define 	BTN5_GPIO 				GPIOA,GPIO_PIN_8
#define 	BTN6_GPIO 				GPIOA,GPIO_PIN_9
#define 	BTN7_GPIO 				GPIOA,GPIO_PIN_10
#define 	BTN8_GPIO 				GPIOB,GPIO_PIN_3
#define 	BTN9_GPIO 				GPIOB,GPIO_PIN_4
#define 	BTN10_GPIO 				GPIOB,GPIO_PIN_5
#define 	BTN11_GPIO 				GPIOB,GPIO_PIN_6
#define 	BTN12_GPIO	 			GPIOB,GPIO_PIN_7
	
	
#define 	JOYSTICK_AXIS_NUM		2
#define 	SECONDARY_AXIS_NUM		2
	
#define 	BUTTONS_NUM				12
#define 	LEDS_NUM				4





#define FILTER_WINDOW_SIZE			10

#define ADC_CHANNELS_NUM			6

#define AXIS_NUM					((JOYSTICK_AXIS_NUM) + (SECONDARY_AXIS_NUM))
																
#if (JOYSTICK_AXIS_NUM > 0)
	#define JOYSTICK_AXIS_ENABLED  	1
#else
	#define JOYSTICK_AXIS_ENABLED  	0
#endif

#if (SECONDARY_AXIS_NUM > 0)
	#define SECONDARY_AXIS_ENABLED  	1
#else
	#define SECONDARY_AXIS_ENABLED  	0
#endif

#if (BUTTONS_NUM > 0)
	#define BUTTONS_ENABLED  	1
#else
	#define BUTTONS_ENABLED  	0
#endif

//#define DEVICE_ID1					0x1FFFF7E8
//#define DEVICE_ID2					0x1FFFF7EA
//#define DEVICE_ID3					0x1FFFF7EC
//#define DEVICE_ID4					0x1FFFF7F0



void GPIO_Poll (uint16_t * p_button_state);

*/






















#endif
