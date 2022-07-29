/**
 * @file       application_protection.h
 * @brief 
 * @author     chen yang (yang.chen@dh-robotics.cn)
 * @date       2022-07-22
 * 
 * @copyright  Copyright (c) 2022 by https://www.dh-robotics.com, All Rights Reserved. 
 * 
 * @par        change log:
 * <table>
 * <tr><th>Date             <th>Version    <th>author          <th>Description
 * <tr><td>2022-07-22       <td>1.0        <td>chen yang       <td>
 * </table>
 */

#ifndef _APPLICATION_PROTECTION_H_
#define _APPLICATION_PROTECTION_H_

#include "F2837xD_device.h"

typedef union
{
    Uint64 all;
    struct
    {
        Uint64 VoltageHigh:1;   //bit0
        Uint64 VoltageLow:1;    //bit1
        Uint64 UPhaseInrushOverCur:1;    //bit2
        Uint64 VPhaseInrushOverCur:1;    //bit3
        Uint64 UPhaseContinueOverCur:1;    //bit4
        Uint64 VPhaseContinueOverCur:1;    //bit5
    }bit;
} ERROR_NUMBER_E;

typedef struct PROTECTION_T_
{
    /* error code and error number */
    Uint16 ErrCode;
    ERROR_NUMBER_E ErrNum;
    ERROR_NUMBER_E ErrNumFirst;

    /* upper computer set parameters */
    struct
    {
        float32 Voltage_Low_Limit;
        float32 Voltage_High_Limit;
        float32 Current_U_Phase_Inrush;
        float32 Current_V_Phase_Inrush;
        float32 Current_U_Phase_Continue;
        float32 Current_V_Phase_Continue;
        float32 Current_U_Phase_Continue_TimeS;
        float32 Current_V_Phase_Continue_TimeS;
    } ComputerSetParam;
    void (*fInit)(struct PROTECTION_T_ *pHandle);/* different motor use different limits */
    void (*fReset)(struct PROTECTION_T_ *pHandle);

    /* bit0: over voltage */
    struct
    {
        bool_t Enable;
        Uint16 ErrCode;
        float32 *Limit;
    } dOverVolCheck;
    void (*fOverVoltageCheck)(struct PROTECTION_T_ *pHandle, float Voltage);

    /* bit1: under voltage */
    struct
    {
        bool_t Enable;
        Uint16 ErrCode;
        float32 *Limit;
    } dUnderVolCheck;
    void (*fUnderVoltageCheck)(struct PROTECTION_T_ *pHandle, float Voltage);

    /* bit2: U phase inrush over current */
    struct
    {
        bool_t Enable;
        Uint16 ErrCode;
        float32 *Limit;
    } dUPhaseInrushOverCur;
    void (*fUPhaseInrushOverCurCheck)(struct PROTECTION_T_ *pHandle, float UPhaseCur);

    /* bit3: V phase inrush over current */
    struct
    {
        bool_t Enable;
        Uint16 ErrCode;
        float32 *Limit;
    } dVPhaseInrushOverCur;
    void (*fVPhaseInrushOverCurCheck)(struct PROTECTION_T_ *pHandle, float VPhaseCur);

    /* bit4: U phase continue over current */
    struct
    {
        bool_t Enable;
        Uint16 ErrCode;
        float32 *Limit;
        float32 *ContinueTimeS;
        Uint32 Count;
    } dUPhaseContinueOverCur;
    void (*fUPhaseContinueOverCurCheck)(struct PROTECTION_T_ *pHandle, float UPhaseCur, float32 Hz);

    /* bit5: V phase continue over current */
    struct
    {
        bool_t Enable;
        Uint16 ErrCode;
        float32 *Limit;
        float32 *ContinueTimeS;
        Uint32 Count;
    } dVPhaseContinueOverCur;
    void (*fVPhaseContinueOverCurCheck)(struct PROTECTION_T_ *pHandle, float VPhaseCur, float32 Hz);

} PROTECTION_T;

extern PROTECTION_T PROTECTION;

#endif  /* _APPLICATION_PROTECTION_H_ */
