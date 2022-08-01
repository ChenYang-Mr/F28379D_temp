/*
 * @Author       : CY [yang.chen@dh-robotics.cn]
 * @Date         : 2022-07-08 15:31:52
 * @LastEditors  : CY [yang.chen@dh-robotics.cn]
 * @LastEditTime : 2022-07-29 11:15:16
 * @FilePath     : \28379d_CPU1_temp\06_user\memory_onchipflash.h
 * @Description  : 
 * Copyright (c) 2022 by https://www.dh-robotics.com, All Rights Reserved. 
 */

#ifndef _DRIVER_ONCHIPFLASH_H_
#define _DRIVER_ONCHIPFLASH_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <F2837xD_device.h>
#include "F28x_Project.h"

#define WORDS_IN_FLASH_BUFFER 0xFF

//
// Defines
//
#define Bzero_SectorN_start         0xBE000
#define Bzero_SectorN_End           0xBFFFF

#define Bzero_SectorM_start         0xBC000
#define Bzero_SectorM_End           0xBDFFF

#define Bzero_SectorL_start         0xBA000
#define Bzero_SectorL_End           0xBBFFF

#define Bzero_SectorK_start         0xB8000
#define Bzero_SectorK_End           0xB9FFF

#define Bzero_SectorJ_start         0xB0000
#define Bzero_SectorJ_End           0xB7FFF

#define Bzero_SectorI_start         0xA8000
#define Bzero_SectorI_End           0xAFFFF

#define Bzero_SectorH_start         0xA0000
#define Bzero_SectorH_End           0xA7FFF

#define Bzero_SectorG_start         0x98000
#define Bzero_SectorG_End           0x9FFFF

#define Bzero_SectorF_start         0x90000
#define Bzero_SectorF_End           0x97FFF

#define Bzero_SectorE_start         0x88000
#define Bzero_SectorE_End           0x8FFFF

#define Bzero_SectorD_start	        0x86000
#define Bzero_SectorD_End	        0x87FFF

#define Bzero_SectorC_start	        0x84000
#define Bzero_SectorC_End	        0x85FFF

#define Bzero_SectorB_start         0x82000
#define Bzero_SectorB_End	        0x83FFF

#define Bzero_SectorA_start	        0x80000
#define Bzero_SectorA_End           0x81FFF

#define Bzero_16KSector_u32length   0x1000
#define Bzero_64KSector_u32length   0x4000

//
// End of file
//


typedef struct{
    Uint16 WDataBuff[WORDS_IN_FLASH_BUFFER + 1];
    Uint16 RDataBuff[WORDS_IN_FLASH_BUFFER + 1];
    Uint32 MaxDelayCount;//0-4294967295

} DATA_ONCHIPFLASH_T;

extern DATA_ONCHIPFLASH_T Data_OnChipFlash;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _DRIVER_ONCHIPFLASH_H_ */
