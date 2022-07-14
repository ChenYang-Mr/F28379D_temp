/*
 * @Author       : CY [2584623834@qq.com]
 * @Date         : 2022-07-08 18:10:56
 * @LastEditors  : CY [2584623834@qq.com]
 * @LastEditTime : 2022-07-08 21:29:17
 * @FilePath     : \28379d_CPU1_temp\06_user\spi_F28379DSpiA.c
 * @Description  :
 * Copyright (c) 2022 by https://www.dh-robotics.com, All Rights Reserved.
 */

 #include "driver_spi.h"


SPI_STATUS_T F28379DSpi_Init(SPI_T *pHandle);
SPI_STATUS_T F28379DSpi_Transfer(SPI_T *pHandle, Uint16 wData, Uint16 *rData);

SPI_T SPI_28379DSPIA = {

    .pData_F28379SPI = &Data_F28379SpiA,

    .fInit = F28379DSpi_Init,
    .fTransfer = F28379DSpi_Transfer
};
