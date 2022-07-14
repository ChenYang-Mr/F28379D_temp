/*
 * @Author       : CY [2584623834@qq.com]
 * @Date         : 2022-07-08 15:31:14
 * @LastEditors  : CY [2584623834@qq.com]
 * @LastEditTime : 2022-07-08 21:28:26
 * @FilePath     : \28379d_CPU1_temp\06_user\driver_DRV8305.c
 * @Description  : 
 * Copyright (c) 2022 by https://www.dh-robotics.com, All Rights Reserved. 
 */

#include "device_driver.h"

DRIVER_STATUS_T DRV8305_Init(DRIVER_T *pHandle);
DRIVER_STATUS_T DRV8305_ReadStatusReg(DRIVER_T *pHandle);
DRIVER_STATUS_T DRV8305_WriteCtrlReg(DRIVER_T *pHandle);
DRIVER_STATUS_T DRV8305_Enable(DRIVER_T *pHandle);
DRIVER_STATUS_T DRV8305_Disable(DRIVER_T *pHandle);

DRIVER_T DRIVER = {
    .pData_DRV8305  = &Data_DRV8305,

    .fInit          = DRV8305_Init,
    .fReadStatusReg = DRV8305_ReadStatusReg,
    .fWriteCtrlReg  = DRV8305_WriteCtrlReg
};
