/*
 * @Author       : CY [yang.chen@dh-robotics.cn]
 * @Date         : 2022-07-08 15:31:14
 * @LastEditors  : CY [yang.chen@dh-robotics.cn]
 * @LastEditTime : 2022-08-02 10:39:17
 * @FilePath     : \F28379D_temp\28379d_CPU1_temp\06_user\device_memory.c
 * @Description  :
 * Copyright (c) 2022 by https://www.dh-robotics.com, All Rights Reserved.
 */

#include "device_memory.h"
#include "memory_onchipflash.h"

MEMORY_STATUS_T Memory_Mapping(MEMORY_T *pHandle);
MEMORY_STATUS_T OnChipFlash_Init(MEMORY_T *pHandle);
MEMORY_STATUS_T OnChipFlash_Read(MEMORY_T *pHandle);
MEMORY_STATUS_T OnChipFlash_Write(MEMORY_T *pHandle);

MEMORY_T MEMORY = {
    .pData_OnChipFlash = &Data_OnChipFlash,

    .fInit = OnChipFlash_Init,
    .fRead = OnChipFlash_Read,
    .fWrite = OnChipFlash_Write,
};
