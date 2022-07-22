/*
 * @Author       : CY [yang.chen@dh-robotics.cn]
 * @Date         : 2022-07-13 14:17:04
 * @LastEditors  : CY [yang.chen@dh-robotics.cn]
 * @LastEditTime : 2022-07-14 09:15:26
 * @FilePath     : \28379d_CPU1_temp\06_user\driver_gpio.c
 * @Description  : gpio driver
 * Copyright (c) 2022 by https://www.dh-robotics.com, All Rights Reserved. 
 */


#include "driver_gpio.h"
#include "F2837xD_IO_assignment.h"


GPIO_STATUS_T F28379Gpio_Init(GPIO_T *pHandle);
GPIO_STATUS_T F28379Gpio_Write(GPIO_T  *pHandle, Uint16 WVal);
GPIO_STATUS_T F28379Gpio_Read(GPIO_T  *pHandle, Uint16 *pRVal);

GPIO_T GPIO_F28379D_EN_GATE = {

    .pData_F28379Gpio = &Data_F28379GpioOutputSyncCpu1,

    .Num = MOTOR1_EN_GATE_GPIO,         //gpio number
    .peripheral = MOTOR1_EN_GATE_MUX,   //gpio muxed pins
    .InitVal = 0,                       //initial value
    
    .fInit = F28379Gpio_Init,
    .fWrite = F28379Gpio_Write,
    .fRead = F28379Gpio_Read
    
};

GPIO_T GPIO_F28379D_WAKE = {

    .pData_F28379Gpio = &Data_F28379GpioOutputSyncCpu1,

    .Num = MOTOR1_EN_GATE_GPIO,         //gpio number
    .peripheral = MOTOR1_WAKE_MUX,   //gpio muxed pins
    .InitVal = 0,                       //initial value

    .fInit = F28379Gpio_Init,
    .fWrite = F28379Gpio_Write,
    .fRead = F28379Gpio_Read

};

GPIO_T GPIO_F28379D_SpiSDI = {

    .pData_F28379Gpio = &Data_F28379GpioInputSyncCpu1,

    .Num = MOTOR1_SDI_GPIO,         //gpio number
    .peripheral = MOTOR1_SDI_MUX,   //gpio muxed pins
    .InitVal = 0,                       //initial value

    .fInit = F28379Gpio_Init,
    .fWrite = F28379Gpio_Write,
    .fRead = F28379Gpio_Read

};


GPIO_T GPIO_F28379D_SpiSDO = {

    .pData_F28379Gpio = &Data_F28379GpioInputSyncCpu1,

    .Num = MOTOR1_SDO_GPIO,         //gpio number
    .peripheral = MOTOR1_SDO_MUX,   //gpio muxed pins
    .InitVal = 0,                       //initial value

    .fInit = F28379Gpio_Init,
    .fWrite = F28379Gpio_Write,
    .fRead = F28379Gpio_Read

};


GPIO_T GPIO_F28379D_SpiCLK = {

    .pData_F28379Gpio = &Data_F28379GpioInputSyncCpu1,

    .Num = MOTOR1_CLK_GPIO,         //gpio number
    .peripheral = MOTOR1_CLK_MUX,   //gpio muxed pins
    .InitVal = 0,                       //initial value

    .fInit = F28379Gpio_Init,
    .fWrite = F28379Gpio_Write,
    .fRead = F28379Gpio_Read

};


GPIO_T GPIO_F28379D_SpiSCS = {

    .pData_F28379Gpio = &Data_F28379GpioOutputSyncCpu1,

    .Num = MOTOR1_SCS_GPIO,         //gpio number
    .peripheral = MOTOR1_SCS_MUX,   //gpio muxed pins
    .InitVal = 0,                       //initial value

    .fInit = F28379Gpio_Init,
    .fWrite = F28379Gpio_Write,
    .fRead = F28379Gpio_Read

};


GPIO_T GPIO_F28379D_PWM1H = {

    .pData_F28379Gpio = &Data_F28379GpioOutputPullupCpu1,

    .Num = MOTOR1_EPWM_AH_GPIO,         //gpio number
    .peripheral = MOTOR1_EPWM_AH_MUX,   //gpio muxed pins
    .InitVal = 0,                       //initial value

    .fInit = F28379Gpio_Init,
    .fWrite = F28379Gpio_Write,
    .fRead = F28379Gpio_Read

};


GPIO_T GPIO_F28379D_PWM1L = {

    .pData_F28379Gpio = &Data_F28379GpioOutputPullupCpu1,

    .Num = MOTOR1_EPWM_AL_GPIO,         //gpio number
    .peripheral = MOTOR1_EPWM_AL_MUX,   //gpio muxed pins
    .InitVal = 0,                       //initial value

    .fInit = F28379Gpio_Init,
    .fWrite = F28379Gpio_Write,
    .fRead = F28379Gpio_Read

};


GPIO_T GPIO_F28379D_PWM2H = {

    .pData_F28379Gpio = &Data_F28379GpioOutputPullupCpu1,

    .Num = MOTOR1_EPWM_BH_GPIO,         //gpio number
    .peripheral = MOTOR1_EPWM_BH_MUX,   //gpio muxed pins
    .InitVal = 0,                       //initial value

    .fInit = F28379Gpio_Init,
    .fWrite = F28379Gpio_Write,
    .fRead = F28379Gpio_Read

};


GPIO_T GPIO_F28379D_PWM2L = {

    .pData_F28379Gpio = &Data_F28379GpioOutputPullupCpu1,

    .Num = MOTOR1_EPWM_BL_GPIO,         //gpio number
    .peripheral = MOTOR1_EPWM_BL_MUX,   //gpio muxed pins
    .InitVal = 0,                       //initial value

    .fInit = F28379Gpio_Init,
    .fWrite = F28379Gpio_Write,
    .fRead = F28379Gpio_Read

};


GPIO_T GPIO_F28379D_PWM3H = {

    .pData_F28379Gpio = &Data_F28379GpioOutputPullupCpu1,

    .Num = MOTOR1_EPWM_CH_GPIO,         //gpio number
    .peripheral = MOTOR1_EPWM_CH_MUX,   //gpio muxed pins
    .InitVal = 0,                       //initial value

    .fInit = F28379Gpio_Init,
    .fWrite = F28379Gpio_Write,
    .fRead = F28379Gpio_Read

};


GPIO_T GPIO_F28379D_PWM3L = {

    .pData_F28379Gpio = &Data_F28379GpioOutputPullupCpu1,

    .Num = MOTOR1_EPWM_CL_GPIO,         //gpio number
    .peripheral = MOTOR1_EPWM_CL_MUX,   //gpio muxed pins
    .InitVal = 0,                       //initial value

    .fInit = F28379Gpio_Init,
    .fWrite = F28379Gpio_Write,
    .fRead = F28379Gpio_Read

};
