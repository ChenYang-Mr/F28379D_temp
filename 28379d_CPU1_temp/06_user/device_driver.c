/*
 * @Author       : CY [yang.chen@dh-robotics.cn]
 * @Date         : 2022-07-08 15:31:14
 * @LastEditors  : CY [yang.chen@dh-robotics.cn]
 * @LastEditTime : 2022-07-15 18:04:08
 * @FilePath     : \F28379D_temp\28379d_CPU1_temp\06_user\device_driver.c
 * @Description  : 
 * Copyright (c) 2022 by https://www.dh-robotics.com, All Rights Reserved. 
 */

#include "device_driver.h"

DRIVER_STATUS_T DRV8305_Init(DRIVER_T *pHandle);
DRIVER_STATUS_T DRV8305_ReadStatusReg(DRIVER_T *pHandle);
DRIVER_STATUS_T DRV8305_WriteCtrlReg(DRIVER_T *pHandle);
DRIVER_STATUS_T DRV8305_Enable(DRIVER_T *pHandle);
DRIVER_STATUS_T DRV8305_Disable(DRIVER_T *pHandle);
DRIVER_STATUS_T DRV8305_PwmSetDuty(struct DRIVER_T_ *pHandle, float32 Ta, float32 Tb, float32 Tc);

DRIVER_T DRIVER = {
    .pData_DRV8305  = &Data_DRV8305,

    .fInit          = DRV8305_Init,
    .fReadStatusReg = DRV8305_ReadStatusReg,
    .fWriteCtrlReg  = DRV8305_WriteCtrlReg,
    .fEnable        = DRV8305_Enable,
    .fDisable       = DRV8305_Disable,
    .fPwmSetDuty   = DRV8305_PwmSetDuty
};
