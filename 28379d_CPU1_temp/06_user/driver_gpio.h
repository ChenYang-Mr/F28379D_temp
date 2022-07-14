/*
 * @Author       : CY [2584623834@qq.com]
 * @Date         : 2022-07-13 14:17:04
 * @LastEditors  : CY [2584623834@qq.com]
 * @LastEditTime : 2022-07-13 17:29:50
 * @FilePath     : \28379d_CPU1_temp\06_user\driver_gpio.h
 * @Description  : gpio driver
 * Copyright (c) 2022 by https://www.dh-robotics.com, All Rights Reserved. 
 */


#ifndef _DRIVER_GPIO_H_
#define _DRIVER_GPIO_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "gpio_F28379D.h"

typedef enum
{
    GPIO_SUCCESS = 0,
    GPIO_FAILURE = 1,
} GPIO_STATUS_T;

typedef struct GPIO_T_
{
    DATA_F28379GPIO_T *pData_F28379Gpio;
    
    Uint16 Num;
    Uint16 peripheral;
    Uint16 InitVal;

    GPIO_STATUS_T (*fInit)(struct GPIO_T_ *pHandle);
    GPIO_STATUS_T (*fWrite)(struct GPIO_T_  *pHandle, Uint16 WVal);
    GPIO_STATUS_T (*fRead)(struct GPIO_T_  *pHandle, Uint16 *pRVal);
} GPIO_T;

extern GPIO_T GPIO_28379D;
extern GPIO_T GPIO_DRV8305_EN_GATE;
extern GPIO_T GPIO_DRV8305_WAKE;
extern GPIO_T GPIO_DRV8305_SpiSDI;
extern GPIO_T GPIO_DRV8305_SpiSDO;
extern GPIO_T GPIO_DRV8305_SpiCLK;
extern GPIO_T GPIO_DRV8305_SpiSCS;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _DRIVER_GPIO_H_ */
