/*
 * @Author       : CY [yang.chen@dh-robotics.cn]
 * @Date         : 2022-07-08 18:11:29
 * @LastEditors  : CY [yang.chen@dh-robotics.cn]
 * @LastEditTime : 2022-07-15 15:28:20
 * @FilePath     : \F28379D_temp\28379d_CPU1_temp\06_user\driver_spi.h
 * @Description  : 
 * Copyright (c) 2022 by https://www.dh-robotics.com, All Rights Reserved. 
 */

#ifndef _DRIVER_SPI_H_
#define _DRIVER_SPI_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <spi_F28379DSpi.h>

typedef enum
{
    SPI_SUCCESS = 0,
    SPI_FAILURE = 1,
} SPI_STATUS_T;

typedef struct SPI_T_
{
    DATA_F28379SPI_T *pData_F28379SPI;

    SPI_STATUS_T (*fInit)(struct SPI_T_ *pHandle);
    SPI_STATUS_T (*fTransfer)(struct SPI_T_  *pHandle, Uint16 wData, Uint16 *rData);
} SPI_T;

extern SPI_T SPI_28379D_SPIA;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _DRIVER_SPI_H_ */
