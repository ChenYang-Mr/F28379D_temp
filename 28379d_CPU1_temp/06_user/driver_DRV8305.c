/*
 * @Author       : CY [yang.chen@dh-robotics.cn]
 * @Date         : 2022-07-08 15:31:14
 * @LastEditors  : CY [yang.chen@dh-robotics.cn]
 * @LastEditTime : 2022-07-18 10:03:41
 * @FilePath     : \F28379D_temp\28379d_CPU1_temp\06_user\driver_DRV8305.c
 * @Description  : 
 * Copyright (c) 2022 by https://www.dh-robotics.com, All Rights Reserved. 
 */

#include "device_driver.h"
#include "driver_DRV8305.h"
#include "driver_spi.h"
#include "driver_gpio.h"
#include "F2837xD_Examples.h"//Delay

static DRIVER_STATUS_T DRV8305ReadSingleReg(DRIVER_T *pHandle, Uint16 address, Uint16 *pData, Uint16 mask);
static DRIVER_STATUS_T DRV8305WriteSingleReg(DRIVER_T *pHandle, Uint16 address, Uint16 data);

DATA_DRV8305_T Data_DRV8305 = {
    .RegRead = {0},
    .RegWrite = DRV8305_REG_DEFAULT,

    .pSpi = &SPI_28379D_SPIA,
    
    .pPwmA = &PWM_F28379D_PWM1,
    .pPwmB = &PWM_F28379D_PWM2,
    .pPwmC = &PWM_F28379D_PWM3,

    .pPin_EnGate = &GPIO_F28379D_EN_GATE,
    .pPin_Wake   = &GPIO_F28379D_WAKE,
    .pPin_SpiSDI = &GPIO_F28379D_SpiSDI,
    .pPin_SpiSDO = &GPIO_F28379D_SpiSDO,
    .pPin_SpiCLK = &GPIO_F28379D_SpiCLK,
    .pPin_SpiSCS = &GPIO_F28379D_SpiSCS,

    .pPin_PwmAH = &GPIO_F28379D_PWM1H,
    .pPin_PwmAL = &GPIO_F28379D_PWM1L,
    .pPin_PwmBH = &GPIO_F28379D_PWM2H,
    .pPin_PwmBL = &GPIO_F28379D_PWM2L,
    .pPin_PwmCH = &GPIO_F28379D_PWM3H,
    .pPin_PwmCL = &GPIO_F28379D_PWM3L
};

DRIVER_STATUS_T DRV8305_ReadStatusReg(DRIVER_T *pHandle)
{
    DRIVER_STATUS_T status = DRIVER_SUCCESS;
    DATA_DRV8305_T *pData = pHandle->pData_DRV8305;

    /* read all status registers */
    status |= DRV8305ReadSingleReg(pHandle, DRV8305_S1_WWD_ADDR,              &pData->RegRead.status1_wwd.all,    DRV8305_S1_WWD_ADDR_MASK);                                // read DRV8305 status reg 1
    status |= DRV8305ReadSingleReg(pHandle, DRV8305_S2_OV_VDS_FAULTS_ADDR,    &pData->RegRead.status2_ov_vds.all, DRV8305_S2_OV_VDS_FAULTS_ADDR_MASK);                      // read DRV8305 status reg 2
    status |= DRV8305ReadSingleReg(pHandle, DRV8305_S3_IC_FAULTS_ADDR,        &pData->RegRead.status3_IC.all,     DRV8305_S3_IC_FAULTS_ADDR_MASK);                          // read DRV8305 status reg 3
    status |= DRV8305ReadSingleReg(pHandle, DRV8305_S4_GD_VGS_FAULTS_ADDR,    &pData->RegRead.status4_gd_Vgs.all, DRV8305_S4_GD_VGS_FAULTS_ADDR_MASK);                      // read DRV8305 status reg 4
    return status;
}

DRIVER_STATUS_T DRV8305_WriteCtrlReg(DRIVER_T *pHandle)
{
    int i;
    DRIVER_STATUS_T status = DRIVER_SUCCESS;
    DATA_DRV8305_T *pData = pHandle->pData_DRV8305;
    Uint16 *wReg = &pData->RegWrite.cntrl5_hs_gd.all;
    Uint16 *rReg = &pData->RegRead.cntrl5_hs_gd.all;

    /* write all control registers */
    status |= DRV8305WriteSingleReg(pHandle, DRV8305_C5_HS_GATE_DRIVER_CNTRL_ADDR, pData->RegWrite.cntrl5_hs_gd.all);     // read DRV8305 control reg 5
    status |= DRV8305WriteSingleReg(pHandle, DRV8305_C6_LS_GATE_DRIVER_CNTRL_ADDR, pData->RegWrite.cntrl6_ls_gd.all);     // read DRV8305 control reg 6
    status |= DRV8305WriteSingleReg(pHandle, DRV8305_C7_GD_CNTRL_ADDR,             pData->RegWrite.cntrl7_gd.all);        // read DRV8305 control reg 7
    status |= DRV8305WriteSingleReg(pHandle, DRV8305_C9_IC_OPS_ADDR,               pData->RegWrite.cntrl9_IC_ops.all);    // read DRV8305 control reg 9
    status |= DRV8305WriteSingleReg(pHandle, DRV8305_CA_SHUNT_AMP_CNTRL_ADDR,      pData->RegWrite.cntrlA_shunt_amp.all); // read DRV8305 control reg A
    status |= DRV8305WriteSingleReg(pHandle, DRV8305_CB_VREG_CNTRL_ADDR,           pData->RegWrite.cntrlB_Vreg.all);      // read DRV8305 control reg B
    status |= DRV8305WriteSingleReg(pHandle, DRV8305_CC_VDS_SNS_CNTRL_ADDR,        pData->RegWrite.cntrlC_Vds_SNS.all);   // read DRV8305 control reg C

    /* read all control registers */
    status |= DRV8305ReadSingleReg(pHandle, DRV8305_C5_HS_GATE_DRIVER_CNTRL_ADDR, &pData->RegRead.cntrl5_hs_gd.all,        DRV8305_C5_HS_GATE_DRIVER_CNTRL_ADDR_MASK);    // read DRV8305 control reg 5
    status |= DRV8305ReadSingleReg(pHandle, DRV8305_C6_LS_GATE_DRIVER_CNTRL_ADDR, &pData->RegRead.cntrl6_ls_gd.all,        DRV8305_C6_LS_GATE_DRIVER_CNTRL_ADDR_MASK);    // read DRV8305 control reg 6
    status |= DRV8305ReadSingleReg(pHandle, DRV8305_C7_GD_CNTRL_ADDR,             &pData->RegRead.cntrl7_gd.all,           DRV8305_C7_GD_CNTRL_ADDR_MASK);                // read DRV8305 control reg 7
    status |= DRV8305ReadSingleReg(pHandle, DRV8305_C9_IC_OPS_ADDR,               &pData->RegRead.cntrl9_IC_ops.all,       DRV8305_C9_IC_OPS_ADDR_MASK);                  // read DRV8305 control reg 9
    status |= DRV8305ReadSingleReg(pHandle, DRV8305_CA_SHUNT_AMP_CNTRL_ADDR,      &pData->RegRead.cntrlA_shunt_amp.all,    DRV8305_CA_SHUNT_AMP_CNTRL_ADDR_MASK);         // read DRV8305 control reg A
    status |= DRV8305ReadSingleReg(pHandle, DRV8305_CB_VREG_CNTRL_ADDR,           &pData->RegRead.cntrlB_Vreg.all,         DRV8305_CB_VREG_CNTRL_ADDR_MASK);              // read DRV8305 control reg B
    status |= DRV8305ReadSingleReg(pHandle, DRV8305_CC_VDS_SNS_CNTRL_ADDR,        &pData->RegRead.cntrlC_Vds_SNS.all,      DRV8305_CC_VDS_SNS_CNTRL_ADDR_MASK);           // read DRV8305 control reg C

    for(i = 5; i < 13; i++)
    {
        if(i != 8)
        {
            if(wReg[i] != rReg[i])
                status |= DRIVER_FAULT;
        }
    }
    return status;
}

DRIVER_STATUS_T DRV8305_Enable(DRIVER_T *pHandle)
{
    DRIVER_STATUS_T status = DRIVER_SUCCESS;

    pHandle->pData_DRV8305->pPin_EnGate->fWrite(pHandle->pData_DRV8305->pPin_EnGate, 1);

    return status;
}

DRIVER_STATUS_T DRV8305_Disable(DRIVER_T *pHandle)
{
    DRIVER_STATUS_T status = DRIVER_SUCCESS;

    pHandle->pData_DRV8305->pPin_EnGate->fWrite(pHandle->pData_DRV8305->pPin_EnGate, 0);

    return status;
}

DRIVER_STATUS_T DRV8305_PwmSetDuty(struct DRIVER_T_ *pHandle, float32 Ta, float32 Tb, float32 Tc)
{
    DRIVER_STATUS_T status = DRIVER_SUCCESS;

    pHandle->pData_DRV8305->pPwmA->fSetDuty(pHandle->pData_DRV8305->pPwmA, Ta);
    pHandle->pData_DRV8305->pPwmB->fSetDuty(pHandle->pData_DRV8305->pPwmB, Tb);
    pHandle->pData_DRV8305->pPwmC->fSetDuty(pHandle->pData_DRV8305->pPwmC, Tc);

    return status;
}


DRIVER_STATUS_T DRV8305_Init(DRIVER_T *pHandle)
{
    DRIVER_STATUS_T status = DRIVER_SUCCESS;

    /* SPI Initial*/
    pHandle->pData_DRV8305->pSpi->fInit(pHandle->pData_DRV8305->pSpi);

#if 0
    /* PWM Initial */
    pHandle->pData_DRV8305->pPwmA->fInit(pHandle->pData_DRV8305->pPwmA);
    pHandle->pData_DRV8305->pPwmB->fInit(pHandle->pData_DRV8305->pPwmB);
    pHandle->pData_DRV8305->pPwmC->fInit(pHandle->pData_DRV8305->pPwmC);


    /* PWM Sync */
    pHandle->pData_DRV8305->pPwmB->fSync(pHandle->pData_DRV8305->pPwmB);
    pHandle->pData_DRV8305->pPwmC->fSync(pHandle->pData_DRV8305->pPwmC);
#endif

    /* EnGate pin Initial*/
    pHandle->pData_DRV8305->pPin_EnGate->fInit(pHandle->pData_DRV8305->pPin_EnGate);

    /* Wake pin Initial*/
    pHandle->pData_DRV8305->pPin_Wake->fInit(pHandle->pData_DRV8305->pPin_Wake);

    /* SDI pin Initial*/
    pHandle->pData_DRV8305->pPin_SpiSDI->fInit(pHandle->pData_DRV8305->pPin_SpiSDI);

    /* SDO pin Initial*/
    pHandle->pData_DRV8305->pPin_SpiSDO->fInit(pHandle->pData_DRV8305->pPin_SpiSDO);

    /* CLK pin Initial*/
    pHandle->pData_DRV8305->pPin_SpiCLK->fInit(pHandle->pData_DRV8305->pPin_SpiCLK);

    /* SCS pin Initial*/
    pHandle->pData_DRV8305->pPin_SpiSCS->fInit(pHandle->pData_DRV8305->pPin_SpiSCS);

    /* AH pin Initial*/
    pHandle->pData_DRV8305->pPin_PwmAH->fInit(pHandle->pData_DRV8305->pPin_PwmAH);

    /* AL pin Initial*/
    pHandle->pData_DRV8305->pPin_PwmAL->fInit(pHandle->pData_DRV8305->pPin_PwmAL);

    /* BH pin Initial*/
    pHandle->pData_DRV8305->pPin_PwmBH->fInit(pHandle->pData_DRV8305->pPin_PwmBH);

    /* BL pin Initial*/
    pHandle->pData_DRV8305->pPin_PwmBL->fInit(pHandle->pData_DRV8305->pPin_PwmBL);

    /* CH pin Initial*/
    pHandle->pData_DRV8305->pPin_PwmCH->fInit(pHandle->pData_DRV8305->pPin_PwmCH);

    /* CL pin Initial*/
    pHandle->pData_DRV8305->pPin_PwmCL->fInit(pHandle->pData_DRV8305->pPin_PwmCL);

//    status |= DRV8305_Enable(pHandle);

    /* read write control registers */
    status |= DRV8305_WriteCtrlReg(pHandle);
    
    /* read status registers */
    status |= DRV8305_ReadStatusReg(pHandle);

    return status;
}

static DRIVER_STATUS_T DRV8305ReadSingleReg(DRIVER_T *pHandle, Uint16 address, Uint16 *pData, Uint16 mask)
{
    DRIVER_STATUS_T status = DRIVER_SUCCESS;
    union DRV830x_SPI_WRITE_WORD_REG w;
    Uint16 rData;

    w.bit.R_W = 1;                          // read - 1
    w.bit.ADDRESS = address;                // load the address
    w.bit.DATA = 0;                         // data to be written

    if(SPI_SUCCESS != pHandle->pData_DRV8305->pSpi->fTransfer(pHandle->pData_DRV8305->pSpi, w.all, &rData))
    {
        status = DRIVER_FAULT;
    }

//    DELAY_US(1);
//
//    if(SPI_SUCCESS != pHandle->pData_DRV8305->pSpi->fTransfer(pHandle->pData_DRV8305->pSpi, 0, &rData))
//    {
//        status = DRIVER_FAULT;
//    }

    *pData = rData & mask;

    return status;
}

static DRIVER_STATUS_T DRV8305WriteSingleReg(DRIVER_T *pHandle, Uint16 address, Uint16 data)
{
    DRIVER_STATUS_T status = DRIVER_SUCCESS;
    union DRV830x_SPI_WRITE_WORD_REG w;
    Uint16 rData;
    Uint16 * cntrlReg;
    
    cntrlReg = (Uint16 *) &(pHandle->pData_DRV8305->RegWrite.Rsvd0);

    w.bit.R_W = 0;                          // write - 0
    w.bit.ADDRESS = address;                // load the address
    w.bit.DATA = cntrlReg[address];         // data to be written
    if(SPI_SUCCESS != pHandle->pData_DRV8305->pSpi->fTransfer(pHandle->pData_DRV8305->pSpi, w.all, &rData))
    {
        status = DRIVER_FAULT;
    }
    return(status);
}

