/*
 * @Author       : CY [yang.chen@dh-robotics.cn]
 * @Date         : 2022-07-15 14:54:38
 * @LastEditors  : CY [yang.chen@dh-robotics.cn]
 * @LastEditTime : 2022-07-15 18:15:14
 * @FilePath     : \F28379D_temp\28379d_CPU1_temp\06_user\driver_pwm.c
 * @Description  : 
 * Copyright (c) 2022 by https://www.dh-robotics.com, All Rights Reserved. 
 */


 #include "driver_pwm.h"


PWM_STATUS_T F28379Pwm_Init(PWM_T *pHandle);
PWM_STATUS_T F28379Pwm_Sync(PWM_T *pHandle);
PWM_STATUS_T F28379Pwm_SetDuty(PWM_T *pHandle, float32 duty);

PWM_T PWM_F28379D_PWM1 = {

    .pData_F28379Pwm = &Data_F28379Pwm1,

    .fInit = F28379Pwm_Init,
    .fSync = F28379Pwm_Sync,
    .fSetDuty = F28379Pwm_SetDuty
};

PWM_T PWM_F28379D_PWM2 = {

    .pData_F28379Pwm = &Data_F28379Pwm2,

    .fInit = F28379Pwm_Init,
    .fSync = F28379Pwm_Sync,
    .fSetDuty = F28379Pwm_SetDuty
};

PWM_T PWM_F28379D_PWM3 = {

    .pData_F28379Pwm = &Data_F28379Pwm3,

    .fInit = F28379Pwm_Init,
    .fSync = F28379Pwm_Sync,
    .fSetDuty = F28379Pwm_SetDuty
};

