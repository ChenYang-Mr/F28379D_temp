/*
 * @Author       : CY [2584623834@qq.com]
 * @Date         : 2022-07-08 18:10:56
 * @LastEditors  : CY [2584623834@qq.com]
 * @LastEditTime : 2022-07-08 21:29:17
 * @FilePath     : \28379d_CPU1_temp\06_user\spi_F28379DSpi.c
 * @Description  : 
 * Copyright (c) 2022 by https://www.dh-robotics.com, All Rights Reserved. 
 */

#include "spi_F28379DSpi.h"
#include "driver_spi.h"
#include "F2837xD_IO_assignment.h"
#include "F2837xD_Gpio_defines.h"
#include "F2837xD_GlobalPrototypes.h"

DATA_F28379SPI_T Data_F28379SpiA = {
    .pRegs = &SpiaRegs,
    .MaxTimeOverCount = 500000
};

static void F28379D_InitSpiRegs(volatile struct SPI_REGS *s);

SPI_STATUS_T F28379DSpi_Init(SPI_T *pHandle)
{
    SPI_STATUS_T status = SPI_SUCCESS;

    F28379D_InitSpiRegs(pHandle->pData_F28379SPI->pRegs);

	return(status);
}

SPI_STATUS_T F28379DSpi_Transfer(SPI_T *pHandle, Uint16 wData, Uint16 *rData)
{
    SPI_STATUS_T status = SPI_SUCCESS;

    volatile struct SPI_REGS *s = pHandle->pData_F28379SPI->pRegs;
	s->SPITXBUF = wData;					    // send out the data
	while(s->SPISTS.bit.INT_FLAG == 0)          // wait for the packet to complete
	{
	    pHandle->pData_F28379SPI->MaxTimeOverCount--;
	    if(pHandle->pData_F28379SPI->MaxTimeOverCount == 0)
	    {
	        status = SPI_FAILURE;
	        break;
	    }
	}
	*rData = s->SPIRXBUF;					    // data read to clear the INT_FLAG bit

	return(status);
}

#if 0
static void F28379D_InitSpiGpio(DATA_F28379SPI_T *pHandle)
{
    // set up SDI pin
    GPIO_SetupPinOptions(pHandle->GpioSDI, GPIO_INPUT, GPIO_ASYNC);
    GPIO_SetupPinMux(pHandle->GpioSDI,0,MOTOR1_SDI_MUX);

    // set up SDO pin
    GPIO_SetupPinOptions(pHandle->GpioSDO, GPIO_INPUT, GPIO_ASYNC);
    GPIO_SetupPinMux(pHandle->GpioSDO,0,MOTOR1_SDO_MUX);

    // set up CLK pin
    GPIO_SetupPinOptions(pHandle->GpioCLK, GPIO_INPUT, GPIO_ASYNC);
    GPIO_SetupPinMux(pHandle->GpioCLK,0,MOTOR1_CLK_MUX);

    // set up SCS pin
    GPIO_SetupPinOptions(pHandle->GpioSCS, GPIO_OUTPUT, GPIO_ASYNC);
    GPIO_SetupPinMux(pHandle->GpioSCS,0,MOTOR1_SCS_MUX);

    return;
}
#endif

static void F28379D_InitSpiRegs(volatile struct SPI_REGS *s)
{
    s->SPICCR.bit.SPISWRESET = 0;       // Put SPI in reset state
    s->SPICCR.bit.SPICHAR = 0xF;        // 16-bit character
    s->SPICCR.bit.SPILBK = 0;           // loopback off
    s->SPICCR.bit.CLKPOLARITY = 0;      // Rising edge without delay

    s->SPICTL.bit.SPIINTENA = 0;        // disable SPI interrupt
    s->SPICTL.bit.TALK = 1;             // enable transmission
    s->SPICTL.bit.MASTER_SLAVE = 1;     // master
    s->SPICTL.bit.CLK_PHASE = 0;        // Rising edge without delay
    s->SPICTL.bit.OVERRUNINTENA = 0;    // disable reciever overrun interrupt

    s->SPIBRR.bit.SPI_BIT_RATE = 19;        // SPICLK = LSPCLK / 4 (max SPICLK)

    s->SPICCR.bit.SPISWRESET=1;         // Enable SPI
}
