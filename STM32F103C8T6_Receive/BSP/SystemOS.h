#ifndef __SYSTEMOS_H__
#define __SYSTEMOS_H__

/*定义各种类型(如果冲突,自行去掉)*/
typedef unsigned char       Uint8;
typedef signed   char       Int8;
typedef unsigned short      Uint16;
typedef signed   short      Int16;
typedef unsigned long       Uint32;
typedef signed   long       Int32;
typedef unsigned long long  Uint64;
typedef signed   long long  Int64;
typedef float               F32;
typedef double              F64;

typedef unsigned char       uint8;
typedef signed   char       int8;
typedef unsigned short      uint16;
typedef signed   short      int16;
typedef unsigned long       uint32;
typedef signed   long       int32;
typedef unsigned long long  uint64;
typedef signed   long long  int64;
typedef float               f32;
typedef double              f64;

//#include <iostream>

#include "main.h"
#include "tim.h"
#include "gpio.h"
//#include "spi.h"

#include "usb_device.h"
#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_hid.h"


#include "stdio.h"
#include "string.h"

#include "joystick.h"
#include "NRF24L01.h"






void SystemOS_Init();
void SystemOS_Loop();










#endif
