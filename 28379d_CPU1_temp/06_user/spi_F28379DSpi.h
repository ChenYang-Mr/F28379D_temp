/*
 * @Author       : CY [2584623834@qq.com]
 * @Date         : 2022-07-08 18:11:29
 * @LastEditors  : CY [2584623834@qq.com]
 * @LastEditTime : 2022-07-13 14:22:18
 * @FilePath     : \28379d_CPU1_temp\06_user\spi_F28379DSpi.h
 * @Description  : 
 * Copyright (c) 2022 by https://www.dh-robotics.com, All Rights Reserved. 
 */

#ifndef _SPI_F28379DSPI_H_
#define _SPI_F28379DSPI_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <F2837xD_device.h>
#include <F2837xD_spi.h>

typedef struct
{
    volatile struct SPI_REGS  * pRegs;

    volatile unsigned int MaxTimeOverCount;
} DATA_F28379SPI_T;

extern DATA_F28379SPI_T Data_F28379SpiA;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _SPI_F28379DSPI_H_ */
