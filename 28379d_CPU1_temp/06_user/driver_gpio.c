/*
 * @Author       : CY [2584623834@qq.com]
 * @Date         : 2022-07-13 14:17:04
 * @LastEditors  : CY [2584623834@qq.com]
 * @LastEditTime : 2022-07-13 17:29:40
 * @FilePath     : \28379d_CPU1_temp\06_user\driver_gpio.c
 * @Description  : gpio driver
 * Copyright (c) 2022 by https://www.dh-robotics.com, All Rights Reserved. 
 */


#include "driver_gpio.h"
#include "F2837xD_IO_assignment.h"


GPIO_STATUS_T F28379Gpio_Init(GPIO_T *pHandle);
GPIO_STATUS_T F28379Gpio_Write(GPIO_T  *pHandle, Uint16 WVal);
GPIO_STATUS_T F28379Gpio_Read(GPIO_T  *pHandle, Uint16 *pRVal);

GPIO_T GPIO_DRV8305_EN_GATE = {

    .pData_F28379Gpio = &Data_F28379GpioOutputSyncCpu1,

    .Num = MOTOR1_EN_GATE_GPIO,         //gpio number
    .peripheral = MOTOR1_EN_GATE_MUX,   //gpio muxed pins
    .InitVal = 0,                       //initial value
    
    .fInit = F28379Gpio_Init,
    .fWrite = F28379Gpio_Write,
    .fRead = F28379Gpio_Read
    
};

GPIO_T GPIO_DRV8305_WAKE = {

    .pData_F28379Gpio = &Data_F28379GpioOutputSyncCpu1,

    .Num = MOTOR1_EN_GATE_GPIO,         //gpio number
    .peripheral = MOTOR1_WAKE_MUX,   //gpio muxed pins
    .InitVal = 0,                       //initial value

    .fInit = F28379Gpio_Init,
    .fWrite = F28379Gpio_Write,
    .fRead = F28379Gpio_Read

};

GPIO_T GPIO_DRV8305_SpiSDI = {

    .pData_F28379Gpio = &Data_F28379GpioInputSyncCpu1,

    .Num = MOTOR1_SDI_GPIO,         //gpio number
    .peripheral = MOTOR1_SDI_MUX,   //gpio muxed pins
    .InitVal = 0,                       //initial value

    .fInit = F28379Gpio_Init,
    .fWrite = F28379Gpio_Write,
    .fRead = F28379Gpio_Read

};


GPIO_T GPIO_DRV8305_SpiSDO = {

    .pData_F28379Gpio = &Data_F28379GpioInputSyncCpu1,

    .Num = MOTOR1_SDO_GPIO,         //gpio number
    .peripheral = MOTOR1_SDO_MUX,   //gpio muxed pins
    .InitVal = 0,                       //initial value

    .fInit = F28379Gpio_Init,
    .fWrite = F28379Gpio_Write,
    .fRead = F28379Gpio_Read

};


GPIO_T GPIO_DRV8305_SpiCLK = {

    .pData_F28379Gpio = &Data_F28379GpioInputSyncCpu1,

    .Num = MOTOR1_CLK_GPIO,         //gpio number
    .peripheral = MOTOR1_CLK_MUX,   //gpio muxed pins
    .InitVal = 0,                       //initial value

    .fInit = F28379Gpio_Init,
    .fWrite = F28379Gpio_Write,
    .fRead = F28379Gpio_Read

};


GPIO_T GPIO_DRV8305_SpiSCS = {

    .pData_F28379Gpio = &Data_F28379GpioOutputSyncCpu1,

    .Num = MOTOR1_SCS_GPIO,         //gpio number
    .peripheral = MOTOR1_SCS_MUX,   //gpio muxed pins
    .InitVal = 0,                       //initial value

    .fInit = F28379Gpio_Init,
    .fWrite = F28379Gpio_Write,
    .fRead = F28379Gpio_Read

};
