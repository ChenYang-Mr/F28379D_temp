/*
 * @Author       : CY [yang.chen@dh-robotics.cn]
 * @Date         : 2022-07-08 15:31:14
 * @LastEditors  : CY [yang.chen@dh-robotics.cn]
 * @LastEditTime : 2022-07-29 11:14:48
 * @FilePath     : \28379d_CPU1_temp\06_user\device_memory.c
 * @Description  : 
 * Copyright (c) 2022 by https://www.dh-robotics.com, All Rights Reserved. 
 */

#include "device_memory.h"
#include "memory_onchipflash.h"

MEMORY_STATUS_T Memory_Mapping(MEMORY_T *pHandle);
MEMORY_STATUS_T OnChipFlash_Init(MEMORY_T *pHandle);
MEMORY_STATUS_T OnChipFlash_Read(MEMORY_T *pHandle);
MEMORY_STATUS_T OnChipFlash_Write(MEMORY_T *pHandle);

//TODO test
int16  Mdata1   = 1;
int32  Mdata2   = 2;
//Uint8  Mdata3   = 3;
Uint16 Mdata4   = 4;
Uint32 Mdata5   = 5;
float32 Mdata6  = 6;
float64 Mdata7  = 7;
Uint64 Mdata8    = 8;
int64 Mdata9     = 9;

MEMORY_T MEMORY = {
    .pData_OnChipFlash  = &Data_OnChipFlash,

    .fInit  = OnChipFlash_Init,
    .fRead  = OnChipFlash_Read,
    .fWrite = OnChipFlash_Write,
//
//
//    .Data[0] = (Uint32*)&Mdata1,
//    .Data[1] = (Uint32*)&Mdata2,
////    .Data[2] = (Uint32*)&Mdata3,
//    .Data[3] = (Uint32*)&Mdata4,
//    .Data[4] = (Uint32*)&Mdata5,
//    .Data[5] = (Uint32*)&Mdata6,
//
//    .Data[6] = (Uint32*)&Mdata7,
//    .Data[7] = ((Uint32*)&Mdata7) + 1,
//    .Data[8] = (Uint32*)&Mdata8,
//    .Data[6] = ((Uint32*)&Mdata8) + 1,
//    .Data[7] = (Uint32*)&Mdata9,
//    .Data[8] = ((Uint32*)&Mdata9) +1
};
// MEMORY_STATUS_T Memory_Mapping(MEMORY_T *pHandle)
// {
//     MEMORY_STATUS_T status = MEMORY_SUCCESS;
//    pHandle.Data[0] = (Uint32*)&Mdata1;
//    pHandle.Data[1] = (Uint32*)&Mdata1;
//    pHandle.Data[2] = (Uint32*)&Mdata1;
//    pHandle.Data[3] = (Uint32*)&Mdata1;
//    pHandle.Data[4] = (Uint32*)&Mdata1;
//    pHandle.Data[5] = (Uint32*)&Mdata1;
//     return(status);
// }
