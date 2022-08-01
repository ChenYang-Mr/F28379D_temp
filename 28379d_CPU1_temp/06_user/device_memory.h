/**
 * @file       device_memory.h
 * @brief 
 * @author     chen yang (yang.chen@dh-robotics.cn)
 * @date       2022-07-28
 * 
 * @copyright  Copyright (c) 2022 by https://www.dh-robotics.com, All Rights Reserved. 
 * 
 * @par        change log:
 * <table>
 * <tr><th>Date             <th>Version    <th>author          <th>Description
 * <tr><td>2022-07-28       <td>1.0        <td>chen yang       <td>The framework of memory
 * </table>
 */

#ifndef _DEVICE_MEMORY_H_
#define _DEVICE_MEMORY_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <memory_onchipflash.h>
#include <F2837xD_device.h>

typedef enum
{
    MEMORY_SUCCESS = 0,
    MEMORY_FAULT = 1,
} MEMORY_STATUS_T;

#define MAX_MEMORY_DATA_SUM (0xFF)

//typedef struct {
//
//
//}

typedef struct MEMORY_T_
{
    DATA_ONCHIPFLASH_T *pData_OnChipFlash;

    MEMORY_STATUS_T MemoryStatus;
    Uint32 *Data[MAX_MEMORY_DATA_SUM];

    MEMORY_STATUS_T (*fMapping)(struct MEMORY_T_ *pHandle);
    MEMORY_STATUS_T (*fInit)(struct MEMORY_T_ *pHandle);
    MEMORY_STATUS_T (*fRead)(struct MEMORY_T_ *pHandle);
    MEMORY_STATUS_T (*fWrite)(struct MEMORY_T_ *pHandle);
} MEMORY_T;


extern MEMORY_T MEMORY;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _DEVICE_DRIVER_H_ */
