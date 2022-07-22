/*
 * @Author       : CY [yang.chen@dh-robotics.cn]
 * @Date         : 2022-07-13 14:17:04
 * @LastEditors  : CY [yang.chen@dh-robotics.cn]
 * @LastEditTime : 2022-07-15 17:55:13
 * @FilePath     : \F28379D_temp\28379d_CPU1_temp\06_user\driver_gpio.h
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

extern GPIO_T GPIO_F28379D_EN_GATE;
extern GPIO_T GPIO_F28379D_WAKE;
extern GPIO_T GPIO_F28379D_SpiSDI;
extern GPIO_T GPIO_F28379D_SpiSDO;
extern GPIO_T GPIO_F28379D_SpiCLK;
extern GPIO_T GPIO_F28379D_SpiSCS;
extern GPIO_T GPIO_F28379D_PWM1H;
extern GPIO_T GPIO_F28379D_PWM1L;
extern GPIO_T GPIO_F28379D_PWM2H;
extern GPIO_T GPIO_F28379D_PWM2L;
extern GPIO_T GPIO_F28379D_PWM3H;
extern GPIO_T GPIO_F28379D_PWM3L;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _DRIVER_GPIO_H_ */
