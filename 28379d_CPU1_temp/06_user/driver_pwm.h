/*
 * @Author       : CY [yang.chen@dh-robotics.cn]
 * @Date         : 2022-07-15 14:54:38
 * @LastEditors  : CY [yang.chen@dh-robotics.cn]
 * @LastEditTime : 2022-07-15 18:11:38
 * @FilePath     : \F28379D_temp\28379d_CPU1_temp\06_user\driver_pwm.h
 * @Description  : 
 * Copyright (c) 2022 by https://www.dh-robotics.com, All Rights Reserved. 
 */


#ifndef _DRIVER_PWM_H_
#define _DRIVER_PWM_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <F2837xD_device.h>
#include "pwm_F28379D.h"

typedef enum
{
    PWM_SUCCESS = 0,
    PWM_FAILURE = 1,
} PWM_STATUS_T;

typedef struct PWM_T_
{
    DATA_F28379PWM_T *pData_F28379Pwm;

    PWM_STATUS_T (*fInit)(struct PWM_T_ *pHandle);
    PWM_STATUS_T (*fSync)(struct PWM_T_  *pHandle);
    PWM_STATUS_T (*fSetDuty)(struct PWM_T_  *pHandle, float32 duty);
} PWM_T;

extern PWM_T PWM_F28379D_PWM1;
extern PWM_T PWM_F28379D_PWM2;
extern PWM_T PWM_F28379D_PWM3;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _DRIVER_PWM_H_ */
