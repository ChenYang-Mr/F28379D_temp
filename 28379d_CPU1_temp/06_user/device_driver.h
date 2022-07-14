/*
 * @Author       : CY [2584623834@qq.com]
 * @Date         : 2022-07-08 15:31:52
 * @LastEditors  : CY [2584623834@qq.com]
 * @LastEditTime : 2022-07-08 19:09:26
 * @FilePath     : \simulink_project\Device\Driver\driver_DRV8305.h
 * @Description  : 
 * Copyright (c) 2022 by https://www.dh-robotics.com, All Rights Reserved. 
 */

#ifndef _DEVICE_DRIVER_H_
#define _DEVICE_DRIVER_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "driver_DRV8305.h"

typedef enum
{
    DRIVER_SUCCESS = 0,
    DRIVER_FAULT = 1,
} DRIVER_STATUS_T;

typedef struct DRIVER_T_
{
    DATA_DRV8305_T *pData_DRV8305;

    DRIVER_STATUS_T DriverStatus;

    DRIVER_STATUS_T (*fInit)(struct DRIVER_T_ *pHandle);
    DRIVER_STATUS_T (*fReadStatusReg)(struct DRIVER_T_ *pHandle);
    DRIVER_STATUS_T (*fWriteCtrlReg)(struct DRIVER_T_ *pHandle);
    DRIVER_STATUS_T (*fEnable)(struct DRIVER_T_ *pHandle);
    DRIVER_STATUS_T (*fDisable)(struct DRIVER_T_ *pHandle);
} DRIVER_T;


extern DRIVER_T DRIVER;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _DEVICE_DRIVER_H_ */
