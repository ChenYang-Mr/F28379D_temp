/*
 * @Author       : CY [yang.chen@dh-robotics.cn]
 * @Date         : 2022-07-08 18:10:56
 * @LastEditors  : CY [yang.chen@dh-robotics.cn]
 * @LastEditTime : 2022-07-15 15:35:23
 * @FilePath     : \F28379D_temp\28379d_CPU1_temp\06_user\driver_spi.c
 * @Description  :
 * Copyright (c) 2022 by https://www.dh-robotics.com, All Rights Reserved.
 */

 #include "driver_spi.h"


SPI_STATUS_T F28379DSpi_Init(SPI_T *pHandle);
SPI_STATUS_T F28379DSpi_Transfer(SPI_T *pHandle, Uint16 wData, Uint16 *rData);

SPI_T SPI_28379D_SPIA = {

    .pData_F28379SPI = &Data_F28379SpiA,

    .fInit = F28379DSpi_Init,
    .fTransfer = F28379DSpi_Transfer
};

