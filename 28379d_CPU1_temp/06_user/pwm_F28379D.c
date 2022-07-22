/*
 * @Author       : CY [yang.chen@dh-robotics.cn]
 * @Date         : 2022-07-15 14:51:29
 * @LastEditors  : CY [yang.chen@dh-robotics.cn]
 * @LastEditTime : 2022-07-16 17:03:53
 * @FilePath     : \F28379D_temp\28379d_CPU1_temp\06_user\pwm_F28379D.c
 * @Description  : 
 * Copyright (c) 2022 by https://www.dh-robotics.com, All Rights Reserved. 
 */

#include "F2837xD_device.h"
#include "F2837xD_EPwm_defines.h"
#include "driver_pwm.h"
#include "pwm_F28379D.h"
#include "F2837xD_epwm.h"
#include "system_setting.h"


#define EPWM1_TIMER_TBPRD  2000  // Period register
#define EPWM1_MAX_CMPA     1950
#define EPWM1_MIN_CMPA       50
#define EPWM1_MAX_CMPB     1950
#define EPWM1_MIN_CMPB       50

DATA_F28379PWM_T Data_F28379Pwm1 = {
    .PwmNum = 1,
    .pRegs = &EPwm1Regs,
    .pCpuReg = &CpuSysRegs
};

DATA_F28379PWM_T Data_F28379Pwm2 = {
    .PwmNum = 2,
    .pRegs = &EPwm2Regs,
    .pCpuReg = &CpuSysRegs
};

DATA_F28379PWM_T Data_F28379Pwm3 = {
    .PwmNum = 3,
    .pRegs = &EPwm3Regs,
    .pCpuReg = &CpuSysRegs
};

PWM_STATUS_T F28379Pwm_Init(PWM_T *pHandle)
{
    PWM_STATUS_T status = PWM_SUCCESS;
    volatile struct EPWM_REGS  *pPwmRegs = pHandle->pData_F28379Pwm->pRegs;

    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;
    EDIS;
#if 0
    EALLOW;

    pPwmRegs->CMPCTL.bit.LOADAMODE = 0x2;  //  @ ctr = PRD or ZERO

	// Time Base SubModule Registers
	pPwmRegs->TBCTL.bit.PRDLD = TB_IMMEDIATE; // set Immediate load
	pPwmRegs->TBPRD = INV_PWM_TBPRD; // PWM frequency = 1 / period
	pPwmRegs->TBPHS.bit.TBPHS = 0;
	pPwmRegs->TBCTR = 0;
	pPwmRegs->TBCTL.bit.CTRMODE   = TB_COUNT_UPDOWN;
	pPwmRegs->TBCTL.bit.HSPCLKDIV = TB_DIV1;
	pPwmRegs->TBCTL.bit.CLKDIV    = TB_DIV1;

	pPwmRegs->TBCTL.bit.PHSEN    = TB_DISABLE;
	pPwmRegs->TBCTL.bit.SYNCOSEL = TB_CTR_ZERO; // sync "down-stream"

	// Counter Compare Submodule Registers
	pPwmRegs->CMPA.bit.CMPA = 0; // set duty 0% initially
	pPwmRegs->CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	pPwmRegs->CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;

	// Action Qualifier SubModule Registers
	pPwmRegs->AQCTLA.bit.CAU = AQ_CLEAR;
	pPwmRegs->AQCTLA.bit.CAD = AQ_SET;

	// Active high complementary PWMs - Disable deadband
	pPwmRegs->DBCTL.bit.OUT_MODE = DB_DISABLE;
    
    EDIS;
    
//    pHandle->pData_F28379Pwm->pCpuReg->PCLKCR0.bit.TBCLKSYNC = 1;   // EPWM CLK enable
#endif

    //
    // Setup TBCLK
    //
    pPwmRegs->TBPRD = EPWM1_TIMER_TBPRD;       // Set timer period 801 TBCLKs
    pPwmRegs->TBPHS.bit.TBPHS = 0x0000;        // Phase is 0
    pPwmRegs->TBCTR = 0x0000;                  // Clear counter

    //
    // Set Compare values
    //
    pPwmRegs->CMPA.bit.CMPA = EPWM1_MIN_CMPA;    // Set compare A value
    pPwmRegs->CMPB.bit.CMPB = EPWM1_MAX_CMPB;    // Set Compare B value

    //
    // Setup counter mode
    //
    pPwmRegs->TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up and down
    pPwmRegs->TBCTL.bit.PHSEN = TB_DISABLE;        // Disable phase loading
    pPwmRegs->TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
    pPwmRegs->TBCTL.bit.CLKDIV = TB_DIV1;

    //
    // Setup shadowing
    //
    pPwmRegs->CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    pPwmRegs->CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    pPwmRegs->CMPCTL.bit.LOADAMODE = CC_CTR_ZERO; // Load on Zero
    pPwmRegs->CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

    //
    // Set actions
    //
    pPwmRegs->AQCTLA.bit.CAU = AQ_SET;            // Set PWM1A on event A, up
                                                  // count
    pPwmRegs->AQCTLA.bit.CAD = AQ_CLEAR;          // Clear PWM1A on event A,
                                                  // down count

    pPwmRegs->AQCTLB.bit.CBU = AQ_SET;            // Set PWM1B on event B, up
                                                  // count
    pPwmRegs->AQCTLB.bit.CBD = AQ_CLEAR;          // Clear PWM1B on event B,
                                                  // down count

    //
    // Interrupt where we will change the Compare Values
    //
    pPwmRegs->ETSEL.bit.INTSEL = ET_CTR_ZERO;     // Select INT on Zero event
    pPwmRegs->ETSEL.bit.INTEN = 1;                // Enable INT
    pPwmRegs->ETPS.bit.INTPRD = ET_3RD;           // Generate INT on 3rd event

    CpuSysRegs.PCLKCR2.all |= 1 << (pHandle->pData_F28379Pwm->PwmNum - 1);

    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EDIS;
	return(status);
}

PWM_STATUS_T F28379Pwm_Sync(PWM_T *pHandle)
{
    PWM_STATUS_T status = PWM_SUCCESS;
    volatile struct EPWM_REGS  *pPwmRegs = pHandle->pData_F28379Pwm->pRegs;
    
    pPwmRegs->TBCTL.bit.SYNCOSEL = TB_SYNC_IN;                 \
	pPwmRegs->TBCTL.bit.PHSEN    = TB_ENABLE;                  \
	pPwmRegs->TBPHS.bit.TBPHS    = 2;                          \
	pPwmRegs->TBCTL.bit.PHSDIR   = TB_UP;

	return(status);
}

PWM_STATUS_T F28379Pwm_SetDuty(PWM_T *pHandle, float32 duty)
{
    PWM_STATUS_T status = PWM_SUCCESS;
    volatile struct EPWM_REGS  *pPwmRegs = pHandle->pData_F28379Pwm->pRegs;

    pPwmRegs->CMPA.bit.CMPA = (Uint16)((1.0F - duty) * INV_PWM_TBPRD);

	return(status);
}


//PWM_STATUS_T F28379Pwm_ClkEnable(PWM_T *pHandle)
//{
//    PWM_STATUS_T status = PWM_SUCCESS;
//    pHandle->pData_F28379Pwm->pCpuReg->PCLKCR0.bit.TBCLKSYNC = 1;   // EPWM CLK enable
//
//    return(status);
//}
