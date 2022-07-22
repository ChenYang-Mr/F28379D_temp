/*
 * @Author       : CY [yang.chen@dh-robotics.cn]
 * @Date         : 2022-07-15 14:51:29
 * @LastEditors  : CY [yang.chen@dh-robotics.cn]
 * @LastEditTime : 2022-07-15 18:09:52
 * @FilePath     : \F28379D_temp\28379d_CPU1_temp\06_user\pwm_F28379D.h
 * @Description  : 
 * Copyright (c) 2022 by https://www.dh-robotics.com, All Rights Reserved. 
 */

#ifndef _PWM_F28379D_H_
#define _PWM_F28379D_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct
{
    Uint16 PwmNum;
    volatile struct EPWM_REGS  *pRegs;
    volatile struct CPU_SYS_REGS *pCpuReg;
} DATA_F28379PWM_T;

extern DATA_F28379PWM_T Data_F28379Pwm1;
extern DATA_F28379PWM_T Data_F28379Pwm2;
extern DATA_F28379PWM_T Data_F28379Pwm3;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _SPI_F28379DSPI_H_ */
