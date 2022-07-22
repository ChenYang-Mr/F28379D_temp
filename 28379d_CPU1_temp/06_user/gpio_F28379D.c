/*
 * @Author       : CY [yang.chen@dh-robotics.cn]
 * @Date         : 2022-07-08 18:10:56
 * @LastEditors  : CY [yang.chen@dh-robotics.cn]
 * @LastEditTime : 2022-07-14 09:13:44
 * @FilePath     : \28379d_CPU1_temp\06_user\gpio_F28379D.c
 * @Description  : 
 * Copyright (c) 2022 by https://www.dh-robotics.com, All Rights Reserved. 
 */

#include "F2837xD_Gpio_defines.h"
#include "gpio_F28379D.h"
#include "driver_gpio.h"
#include "F2837xD_GlobalPrototypes.h"

DATA_F28379GPIO_T Data_F28379GpioOutputSyncCpu1 = {
    .output = GPIO_OUTPUT,
    .flags = GPIO_ASYNC,
    .cpu = GPIO_MUX_CPU1
};

DATA_F28379GPIO_T Data_F28379GpioInputSyncCpu1 = {
    .output = GPIO_INPUT,
    .flags = GPIO_ASYNC,
    .cpu = GPIO_MUX_CPU1
};

DATA_F28379GPIO_T Data_F28379GpioOutputPullupCpu1 = {
    .output = GPIO_OUTPUT,
    .flags = GPIO_PULLUP,
    .cpu = GPIO_MUX_CPU1
};

GPIO_STATUS_T F28379Gpio_Init(GPIO_T *pHandle)
{ 
    GPIO_STATUS_T status = GPIO_SUCCESS;
     
	GPIO_WritePin(pHandle->Num, pHandle->InitVal);  // Disable EN_GATE
	GPIO_SetupPinOptions(pHandle->Num, pHandle->pData_F28379Gpio->output, pHandle->pData_F28379Gpio->flags);
	GPIO_SetupPinMux(pHandle->Num, pHandle->pData_F28379Gpio->cpu, pHandle->peripheral);

	return(status);
}


GPIO_STATUS_T F28379Gpio_Write(GPIO_T  *pHandle, Uint16 WVal)
{
    GPIO_STATUS_T status = GPIO_SUCCESS;

    GPIO_WritePin(pHandle->Num, WVal);

    return(status);

}

GPIO_STATUS_T F28379Gpio_Read(GPIO_T  *pHandle, Uint16 *pRVal)
{
    GPIO_STATUS_T status = GPIO_SUCCESS;

    *pRVal = GPIO_ReadPin(pHandle->Num);

    return(status);
}
