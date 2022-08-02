/*
 * @Author       : CY [yang.chen@dh-robotics.cn]
 * @Date         : 2022-07-08 19:15:35
 * @LastEditors  : CY [yang.chen@dh-robotics.cn]
 * @LastEditTime : 2022-08-02 16:16:11
 * @FilePath     : \F28379D_temp\28379d_CPU1_temp\06_user\main_cpu1.c
 * @Description  :
 * Copyright (c) 2022 by https://www.dh-robotics.com, All Rights Reserved.
 */
//#include "Includes.h"

//#include <F2837xD_device.h>
#include "F2837xD_Ipc_drivers.h"

#include "device.h"
#include "driverlib.h"
//#include "F2837xD_SysCtrl.h"
#include "F2837xD_Pie_defines.h"
#include "device_driver.h"
//#include "F2837xD_GlobalPrototypes.h"
//#include "application_protection.h"
#include "device_memory.h"

//#define delay_s(x) SysCtl_delay(((((long double)(x)) / (1.0L /  \
//                              (long double)DEVICE_SYSCLK_FREQ)) - 9.0L) / 5.0L)

int16 Data1;
int32 Data2;
int64 Data3;
Uint16 Data4;
Uint32 Data5;
Uint64 Data6;
float32 Data7;
float64 Data8;
Uint32 Data9;
Uint64 Data10;
float32 Data11;
float64 Data12;

void OnChipFlash_Write(void);
void main(void)
{
//ȷ������ģʽ
#ifdef _STANDALONE
#ifdef _FLASH

//    IPCBootCPU2(C1C2_BROM_BOOTMODE_BOOT_FROM_FLASH);
#else

    IPCBootCPU2(C1C2_BROM_BOOTMODE_BOOT_FROM_RAM);
#endif
#endif
#if 0
    //�豸��ʼ��
    Device_init();
    //GPIO��ʼ��
    Device_initGPIO();

    Interrupt_initModule();
    Interrupt_initVectorTable();
    //�������ж�
    Interrupt_enableMaster();

    GPIO_setPinConfig(DEVICE_GPIO_CFG_LED1);
    GPIO_setMasterCore(DEVICE_GPIO_PIN_LED1, GPIO_CORE_CPU1);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_LED1, GPIO_PIN_TYPE_STD);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_LED1, GPIO_DIR_MODE_OUT);

    GPIO_setPinConfig(DEVICE_GPIO_CFG_LED2);
    GPIO_setMasterCore(DEVICE_GPIO_PIN_LED2, GPIO_CORE_CPU2);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_LED2, GPIO_PIN_TYPE_STD);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_LED2, GPIO_DIR_MODE_OUT);

#endif

    //
    // Initialize System Control. Enable Peripheral Clocks.
    //
    InitSysCtrl();

    //
    // Disable CPU interrupts.
    //
    DINT;

    //
    // Initialize PIE control registers to default state.
    //
    InitPieCtrl();

    //
    // Disable CPU interrupts and clear all CPU interrupt flags.
    //
    IER = 0x0000;
    IFR = 0x0000;

    //
    // Initialize PIE vector table with pointers to the default
    // Interrupt Service Routines (ISR).
    //
    InitPieVectTable();
    MEMORY_T *pHandle = &MEMORY;

size_t int16_Size = sizeof(int16);
size_t int32_Size = sizeof(int32);
size_t int64_Size = sizeof(int64);
size_t Uint16_Size = sizeof(Uint16);
size_t Uint32_Size = sizeof(Uint32);
size_t Uint64_Size = sizeof(Uint64);
size_t float32_Size = sizeof(float32);
size_t float64_Size = sizeof(float64);

     pHandle->DataWrite.member.Mdata1 = -1;
     pHandle->DataWrite.member.Mdata2 = -2;
     pHandle->DataWrite.member.Mdata3 = -3;
     pHandle->DataWrite.member.Mdata4 = 4;
     pHandle->DataWrite.member.Mdata5 = 5;
     pHandle->DataWrite.member.Mdata6 = 6;
     pHandle->DataWrite.member.Mdata7 = 7.5;
     pHandle->DataWrite.member.Mdata8 = 8.5;
     pHandle->DataWrite.member.Mdata9 = 44;
     pHandle->DataWrite.member.Mdata10 = 666;
     pHandle->DataWrite.member.Mdata11 = 9.9999;
     pHandle->DataWrite.member.Mdata12 = 6.5526;

    // /* memory */
    MEMORY.fInit(&MEMORY);
     MEMORY.fWrite(&MEMORY);
    MEMORY.fRead(&MEMORY);

    Data1 = pHandle->DataRead.member.Mdata1;
    Data2 = pHandle->DataRead.member.Mdata2;
    Data3 = pHandle->DataRead.member.Mdata3;
    Data4 = pHandle->DataRead.member.Mdata4;
    Data5 = pHandle->DataRead.member.Mdata5;
    Data6 = pHandle->DataRead.member.Mdata6;
    Data7 = pHandle->DataRead.member.Mdata7;
    Data8 = pHandle->DataRead.member.Mdata8;
    Data9 = pHandle->DataRead.member.Mdata9;
    Data10 = pHandle->DataRead.member.Mdata10;
    Data11 = pHandle->DataRead.member.Mdata11;
    Data12 = pHandle->DataRead.member.Mdata12;
}
#if 0
//
// epwm1_isr - EPWM1 ISR
//
__interrupt void epwm1_isr(void)
{
    //
    // Update the CMPA and CMPB values
    //
//    update_compare(&epwm1_info);

    DRIVER.fPwmSetDuty(&DRIVER, 0.2, 0.3, 0.5);

    //
    // Clear INT flag for this timer
    //
    EPwm1Regs.ETCLR.bit.INT = 1;

    //
    // Acknowledge this interrupt to receive more interrupts from group 3
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}

//
// epwm2_isr - EPWM2 ISR
//
__interrupt void epwm2_isr(void)
{
    //
    // Update the CMPA and CMPB values
    //
//    update_compare(&epwm2_info);

    //
    // Clear INT flag for this timer
    //
    EPwm2Regs.ETCLR.bit.INT = 1;

    //
    // Acknowledge this interrupt to receive more interrupts from group 3
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}

//
// epwm3_isr - EPWM3 ISR
//
__interrupt void epwm3_isr(void)
{
    //
    // Update the CMPA and CMPB values
    //
//    update_compare(&epwm3_info);

    //
    // Clear INT flag for this timer
    //
    EPwm3Regs.ETCLR.bit.INT = 1;

    //
    // Acknowledge this interrupt to receive more interrupts from group 3
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}
#endif
