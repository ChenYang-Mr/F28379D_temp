/**
 * @file       application_protection.c
 * @brief 
 * @author     chen yang (yang.chen@dh-robotics.cn)
 * @date       2022-07-22
 * 
 * @copyright  Copyright (c) 2022 by https://www.dh-robotics.com, All Rights Reserved. 
 * 
 * @par        change log:
 * <table>
 * <tr><th>Date             <th>Version    <th>author          <th>Description
 * <tr><td>2022-07-22       <td>1.0        <td>chen yang       <td>内容
 * </table>
 */

#include "application_protection.h"

void OverVoltageCheck(PROTECTION_T *pHandle, float Voltage);
void UnderVoltageCheck(PROTECTION_T *pHandle, float Voltage);
void UPhaseInrushOverCurCheck(PROTECTION_T *pHandle, float UPhaseCur);
void VPhaseInrushOverCurCheck(PROTECTION_T *pHandle, float VPhaseCur);
void UPhaseContinueOverCurCheck(struct PROTECTION_T_ *pHandle, float UPhaseCur, float32 Hz);
void VPhaseContinueOverCurCheck(struct PROTECTION_T_ *pHandle, float VPhaseCur, float32 Hz);

PROTECTION_T PROTECTION = 
{
    //TODO 0x3220 is a error data
    .ComputerSetParam =
    {
        .Voltage_Low_Limit                  = 5,
        .Voltage_High_Limit                 = 60,
        .Current_U_Phase_Inrush             = 1,
        .Current_V_Phase_Inrush             = 1,
        .Current_U_Phase_Continue           = 1,
        .Current_V_Phase_Continue           = 1,
        .Current_U_Phase_Continue_TimeS     = 100,
        .Current_V_Phase_Continue_TimeS     = 100,
    },

    /* bit 0 */
    .dOverVolCheck =
    {
        .Enable     = true,
        .ErrCode    = 0x3210,
        .Limit      = &PROTECTION.ComputerSetParam.Voltage_High_Limit,
    },
    .fOverVoltageCheck = OverVoltageCheck,

    /* bit 1 */
    .dUnderVolCheck =
    {
        .Enable     = true,
        .ErrCode    = 0x3220,
        .Limit      = &PROTECTION.ComputerSetParam.Voltage_Low_Limit,
    },
    .fUnderVoltageCheck = UnderVoltageCheck,

    /* bit 2 */
    .dUPhaseInrushOverCur =
    {
        .Enable     = true,
        .ErrCode    = 0x2222,
        .Limit      = &PROTECTION.ComputerSetParam.Current_U_Phase_Inrush,
    },
    .fUPhaseInrushOverCurCheck = UPhaseInrushOverCurCheck,

    /* bit 3 */
    .dVPhaseInrushOverCur =
    {
        .Enable     = true,
        .ErrCode    = 0x2222,
        .Limit      = &PROTECTION.ComputerSetParam.Current_V_Phase_Inrush,
    },
    .fVPhaseInrushOverCurCheck = VPhaseInrushOverCurCheck,

    /* bit4: U phase continue over current */
    .dUPhaseContinueOverCur =
    {
        .Enable         = true,
        .ErrCode        = 0x2222,
        .Limit          = &PROTECTION.ComputerSetParam.Current_U_Phase_Continue,
        .ContinueTimeS  = &PROTECTION.ComputerSetParam.Current_U_Phase_Continue_TimeS,
        .Count          = 0,
    },
    .fUPhaseContinueOverCurCheck = UPhaseContinueOverCurCheck,

    /* bit5: V phase continue over current */
    .dVPhaseContinueOverCur =
    {
        .Enable         = true,
        .ErrCode        = 0x2222,
        .Limit          = &PROTECTION.ComputerSetParam.Current_V_Phase_Continue,
        .ContinueTimeS  = &PROTECTION.ComputerSetParam.Current_V_Phase_Continue_TimeS,
        .Count          = 0,
    },
    .fUPhaseContinueOverCurCheck = VPhaseContinueOverCurCheck,

};


void OverVoltageCheck(PROTECTION_T *pHandle, float Voltage)
{
    if((Voltage > *(pHandle->dOverVolCheck.Limit)) && (pHandle->dUnderVolCheck.Enable))
    {
        pHandle->ErrNum.bit.VoltageHigh = 1;
        if(pHandle->ErrNumFirst.all == 0)
        {
            pHandle->ErrNumFirst.bit.VoltageHigh = 1;
            pHandle->ErrCode = pHandle->dOverVolCheck.ErrCode;
        }
    }
}


void UnderVoltageCheck(PROTECTION_T *pHandle, float Voltage)
{
    if((Voltage < *(pHandle->dUnderVolCheck.Limit)) && (pHandle->dUnderVolCheck.Enable))
    {
        pHandle->ErrNum.bit.VoltageLow = 1;
        if(pHandle->ErrNumFirst.all == 0)
        {
            pHandle->ErrNumFirst.bit.VoltageLow = 1;
            pHandle->ErrCode = pHandle->dUnderVolCheck.ErrCode;
        }
    }
}

void UPhaseInrushOverCurCheck(PROTECTION_T *pHandle, float UPhaseCur)
{
    if((UPhaseCur > *(pHandle->dUPhaseInrushOverCur.Limit)) && (pHandle->dUPhaseInrushOverCur.Enable))
    {
        pHandle->ErrNum.bit.UPhaseInrushOverCur = 1;
        if(pHandle->ErrNumFirst.all == 0)
        {
            pHandle->ErrNumFirst.bit.UPhaseInrushOverCur = 1;
            pHandle->ErrCode = pHandle->dUPhaseInrushOverCur.ErrCode;
        }
    }
}

void VPhaseInrushOverCurCheck(PROTECTION_T *pHandle, float VPhaseCur)
{
    if((VPhaseCur > *(pHandle->dVPhaseInrushOverCur.Limit)) && (pHandle->dVPhaseInrushOverCur.Enable))
    {
        pHandle->ErrNum.bit.VPhaseInrushOverCur = 1;
        if(pHandle->ErrNumFirst.all == 0)
        {
            pHandle->ErrNumFirst.bit.VPhaseInrushOverCur = 1;
            pHandle->ErrCode = pHandle->dVPhaseInrushOverCur.ErrCode;
        }
    }
}

void UPhaseContinueOverCurCheck(struct PROTECTION_T_ *pHandle, float UPhaseCur, float32 Hz)
{
    if((UPhaseCur > *(pHandle->dUPhaseContinueOverCur.Limit)) && (pHandle->dUPhaseContinueOverCur.Enable))
    {
        pHandle->dUPhaseContinueOverCur.Count++;
        if(pHandle->dUPhaseContinueOverCur.Count > (Uint32)(*(pHandle->dUPhaseContinueOverCur.ContinueTimeS) * Hz))
        {
            pHandle->ErrNum.bit.UPhaseContinueOverCur = 1;
            if(pHandle->ErrNumFirst.all == 0)
            {
                pHandle->ErrNumFirst.bit.UPhaseContinueOverCur = 1;
                pHandle->ErrCode = pHandle->dUPhaseContinueOverCur.ErrCode;
            }
        }
    }
    else
    {
        pHandle->dUPhaseContinueOverCur.Count = 0;
    }
    
}
void VPhaseContinueOverCurCheck(struct PROTECTION_T_ *pHandle, float VPhaseCur, float32 Hz)
{
    if((VPhaseCur > *(pHandle->dVPhaseContinueOverCur.Limit)) && (pHandle->dVPhaseContinueOverCur.Enable))
    {
        pHandle->dVPhaseContinueOverCur.Count++;
        if(pHandle->dVPhaseContinueOverCur.Count > (Uint32)(*(pHandle->dVPhaseContinueOverCur.ContinueTimeS) * Hz))
        {
            pHandle->ErrNum.bit.VPhaseContinueOverCur = 1;
            if(pHandle->ErrNumFirst.all == 0)
            {
                pHandle->ErrNumFirst.bit.VPhaseContinueOverCur = 1;
                pHandle->ErrCode = pHandle->dVPhaseContinueOverCur.ErrCode;
            }
        }
    }
    else
    {
        pHandle->dVPhaseContinueOverCur.Count = 0;
    }
    
}
