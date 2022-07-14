/*
 * @Author       : CY [2584623834@qq.com]
 * @Date         : 2022-07-08 18:11:29
 * @LastEditors  : CY [2584623834@qq.com]
 * @LastEditTime : 2022-07-13 17:21:23
 * @FilePath     : \28379d_CPU1_temp\06_user\gpio_F28379D.h
 * @Description  : 
 * Copyright (c) 2022 by https://www.dh-robotics.com, All Rights Reserved. 
 */

#ifndef _GPIO_F28379DGPIO_H_
#define _GPIO_F28379DGPIO_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <F2837xD_device.h>

typedef struct
{
    Uint16 output;
    Uint16 flags;
    Uint16 cpu;
} DATA_F28379GPIO_T;

extern DATA_F28379GPIO_T Data_F28379GpioOutputSyncCpu1;
extern DATA_F28379GPIO_T Data_F28379GpioInputSyncCpu1;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _GPIO_F28379DGPIO_H_ */
