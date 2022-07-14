/*
 * @Author       : CY [2584623834@qq.com]
 * @Date         : 2022-07-08 15:31:14
 * @LastEditors  : CY [2584623834@qq.com]
 * @LastEditTime : 2022-07-11 15:12:50
 * @FilePath     : \28379d_CPU1_temp\06_user\driver_DRV8305.c
 * @Description  : 
 * Copyright (c) 2022 by https://www.dh-robotics.com, All Rights Reserved. 
 */

#include "device_driver.h"
#include "driver_DRV8305.h"
#include "driver_spi.h"
#include "F2837xD_Examples.h"//Delay

static DRIVER_STATUS_T DRV8305ReadSingleReg(DRIVER_T *pHandle, Uint16 address, Uint16 *pData, Uint16 mask);
static DRIVER_STATUS_T DRV8305WriteSingleReg(DRIVER_T *pHandle, Uint16 address, Uint16 data);

DATA_DRV8305_T Data_DRV8305 = {
    .RegRead = {0},
    .RegWrite = {0},

    .pSpi = &SPI_28379DSPIA,

    .pPin_EnGate = &GPIO_DRV8305_EN_GATE,
    .pPin_Wake = &GPIO_DRV8305_WAKE,
    .pPin_SpiSDI = &GPIO_DRV8305_SpiSDI,
    .pPin_SpiSDO = &GPIO_DRV8305_SpiSDO,
    .pPin_SpiCLK = &GPIO_DRV8305_SpiCLK,
    .pPin_SpiSCS = &GPIO_DRV8305_SpiSCS
};

DRIVER_STATUS_T DRV8305_Init(DRIVER_T *pHandle)
{
    DRIVER_STATUS_T status = DRIVER_SUCCESS;
    DATA_DRV8305_T *pData = pHandle->pData_DRV8305;

    /* SPI Initial*/
    pHandle->pData_DRV8305->pSpi->fInit(pHandle->pData_DRV8305->pSpi);

    /* EnGate pin Initial*/
    pHandle->pData_DRV8305->pPin_EnGate->fInit(pHandle->pData_DRV8305->pPin_EnGate);

    /* Wake pin Initial*/
    pHandle->pData_DRV8305->pPin_Wake->fInit(pHandle->pData_DRV8305->pPin_Wake);

    /* Wake pin Initial*/
    pHandle->pData_DRV8305->pPin_SpiSDI->fInit(pHandle->pData_DRV8305->pPin_SpiSDI);

    /* Wake pin Initial*/
    pHandle->pData_DRV8305->pPin_SpiSDO->fInit(pHandle->pData_DRV8305->pPin_SpiSDO);

    /* Wake pin Initial*/
    pHandle->pData_DRV8305->pPin_SpiCLK->fInit(pHandle->pData_DRV8305->pPin_SpiCLK);

    /* Wake pin Initial*/
    pHandle->pData_DRV8305->pPin_SpiSCS->fInit(pHandle->pData_DRV8305->pPin_SpiSCS);

    /* set write register */
    pHandle->pData_DRV8305->RegWrite.cntrl5_hs_gd.all = 0;
    pHandle->pData_DRV8305->RegWrite.cntrl6_ls_gd.all = 0;
    pHandle->pData_DRV8305->RegWrite.cntrl7_gd.all = 0;
    pHandle->pData_DRV8305->RegWrite.cntrl9_IC_ops.all = 0;
    pHandle->pData_DRV8305->RegWrite.cntrlA_shunt_amp.all = 0;
    pHandle->pData_DRV8305->RegWrite.cntrlB_Vreg.all = 0;
    pHandle->pData_DRV8305->RegWrite.cntrlC_Vds_SNS.all = 0;

    pHandle->pData_DRV8305->RegWrite.cntrl5_hs_gd.bit.IDRIVEN_HS = drv8305_idriveN_hs_60mA;
    pHandle->pData_DRV8305->RegWrite.cntrl5_hs_gd.bit.IDRIVEP_HS = drv8305_idriveP_hs_50mA;
    pHandle->pData_DRV8305->RegWrite.cntrl5_hs_gd.bit.TDRIVEN    = drv8305_tdriveN_250nS;

    pHandle->pData_DRV8305->RegWrite.cntrl6_ls_gd.bit.IDRIVEN_LS = drv8305_idriveN_ls_60mA;
    pHandle->pData_DRV8305->RegWrite.cntrl6_ls_gd.bit.IDRIVEP_LS = drv8305_idriveP_ls_50mA;
    pHandle->pData_DRV8305->RegWrite.cntrl6_ls_gd.bit.TDRIVEP    = drv8305_tdriveP_250nS;

    pHandle->pData_DRV8305->RegWrite.cntrl7_gd.bit.COMM_OPTION = drv8305_comm_diode_FW;
    pHandle->pData_DRV8305->RegWrite.cntrl7_gd.bit.PWM_MODE    = drv8305_PWM_mode_3;
    pHandle->pData_DRV8305->RegWrite.cntrl7_gd.bit.DEAD_TIME   = drv8305_deadTime_60nS;
    pHandle->pData_DRV8305->RegWrite.cntrl7_gd.bit.TBLANK      = drv8305_tblank_2us;
    pHandle->pData_DRV8305->RegWrite.cntrl7_gd.bit.TVDS        = drv8305_tblank_4us;

    pHandle->pData_DRV8305->RegWrite.cntrl9_IC_ops.bit.Flip_OTS        = drv8305_disable_OTS;
    pHandle->pData_DRV8305->RegWrite.cntrl9_IC_ops.bit.DIS_VPVDD_UVLO2 = drv8305_enable_PVDD_UVLO2_fault;
    pHandle->pData_DRV8305->RegWrite.cntrl9_IC_ops.bit.DIS_GDRV_FAULT  = drv8305_enable_gdrv_fault;
    pHandle->pData_DRV8305->RegWrite.cntrl9_IC_ops.bit.EN_SNS_CLAMP    = drv8305_disable_Sns_Clamp;
    pHandle->pData_DRV8305->RegWrite.cntrl9_IC_ops.bit.WD_DLY          = drv8305_wd_dly_20mS;
    pHandle->pData_DRV8305->RegWrite.cntrl9_IC_ops.bit.DIS_SNS_OCP     = drv8305_enable_SnsOcp;
    pHandle->pData_DRV8305->RegWrite.cntrl9_IC_ops.bit.WD_EN           = drv8305_disable_WD;
    pHandle->pData_DRV8305->RegWrite.cntrl9_IC_ops.bit.SLEEP           = drv8305_sleep_No;
    pHandle->pData_DRV8305->RegWrite.cntrl9_IC_ops.bit.CLR_FLTS        = drv8305_ClrFaults_No;      // fault clearing bit
    pHandle->pData_DRV8305->RegWrite.cntrl9_IC_ops.bit.SET_VCPH_UV     = drv8305_set_Vcph_UV_4p9V;
    //TODO
//    pHandle->pData_DRV8305->RegWrite.cntrlA_shunt_amp.bit.GAIN_CS1   = (DRV_gain == 10) ? drv8305_gain_CS_10 :
//                                                     (DRV_gain == 20) ? drv8305_gain_CS_20 :
//                                                     (DRV_gain == 40) ? drv8305_gain_CS_40 : drv8305_gain_CS_80;
//    pHandle->pData_DRV8305->RegWrite.cntrlA_shunt_amp.bit.GAIN_CS2   = (DRV_gain == 10) ? drv8305_gain_CS_10 :
//                                                     (DRV_gain == 20) ? drv8305_gain_CS_20 :
//                                                     (DRV_gain == 40) ? drv8305_gain_CS_40 : drv8305_gain_CS_80;
//    pHandle->pData_DRV8305->RegWrite.cntrlA_shunt_amp.bit.GAIN_CS3   = (DRV_gain == 10) ? drv8305_gain_CS_10 :
//                                                     (DRV_gain == 20) ? drv8305_gain_CS_20 :
//                                                     (DRV_gain == 40) ? drv8305_gain_CS_40 : drv8305_gain_CS_80;
    pHandle->pData_DRV8305->RegWrite.cntrlA_shunt_amp.bit.CS_BLANK   = drv8305_cs_blank_0ns;
    pHandle->pData_DRV8305->RegWrite.cntrlA_shunt_amp.bit.DC_CAL_CH1 = drv8305_dc_cal_off;
    pHandle->pData_DRV8305->RegWrite.cntrlA_shunt_amp.bit.DC_CAL_CH2 = drv8305_dc_cal_off;
    pHandle->pData_DRV8305->RegWrite.cntrlA_shunt_amp.bit.DC_CAL_CH3 = drv8305_dc_cal_off;

    pHandle->pData_DRV8305->RegWrite.cntrlB_Vreg.bit.VREF_SCALING   = drv8305_vref_scaling_2;
    pHandle->pData_DRV8305->RegWrite.cntrlB_Vreg.bit.SLEEP_DLY      = drv8305_sleep_dly_10uS;
    pHandle->pData_DRV8305->RegWrite.cntrlB_Vreg.bit.DIS_VREG_PWRGD = 0;                               // temporary //
    pHandle->pData_DRV8305->RegWrite.cntrlB_Vreg.bit.VREG_UV_LEVEL  = drv8305_vreg_UV_level_30percent;

    pHandle->pData_DRV8305->RegWrite.cntrlC_Vds_SNS.bit.VDS_LEVEL   = drv8305_vds_level_1175mV;
    pHandle->pData_DRV8305->RegWrite.cntrlC_Vds_SNS.bit.VDS_MODE    = drv8305_vds_mode_latchedShutDown;

    /* read all status registers */
    status |= DRV8305ReadSingleReg(pHandle, DRV8305_S1_WWD_ADDR,              &pData->RegRead.status1_wwd.all,    DRV8305_S1_WWD_ADDR_MASK);                             // read DRV8305 status reg 1
    status |= DRV8305ReadSingleReg(pHandle, DRV8305_S2_OV_VDS_FAULTS_ADDR,    &pData->RegRead.status2_ov_vds.all, DRV8305_S2_OV_VDS_FAULTS_ADDR_MASK);                   // read DRV8305 status reg 2
    status |= DRV8305ReadSingleReg(pHandle, DRV8305_S3_IC_FAULTS_ADDR,        &pData->RegRead.status3_IC.all,     DRV8305_S3_IC_FAULTS_ADDR_MASK);                       // read DRV8305 status reg 3
    status |= DRV8305ReadSingleReg(pHandle, DRV8305_S4_GD_VGS_FAULTS_ADDR,    &pData->RegRead.status4_gd_Vgs.all, DRV8305_S4_GD_VGS_FAULTS_ADDR_MASK);                   // read DRV8305 status reg 4

    /* read all control registers */
    status |= DRV8305ReadSingleReg(pHandle, DRV8305_C5_HS_GATE_DRIVER_CNTRL_ADDR, &pData->RegRead.cntrl5_hs_gd.all,        DRV8305_C5_HS_GATE_DRIVER_CNTRL_ADDR_MASK);    // read DRV8305 control reg 5
    status |= DRV8305ReadSingleReg(pHandle, DRV8305_C6_LS_GATE_DRIVER_CNTRL_ADDR, &pData->RegRead.cntrl6_ls_gd.all,        DRV8305_C6_LS_GATE_DRIVER_CNTRL_ADDR_MASK);    // read DRV8305 control reg 6
    status |= DRV8305ReadSingleReg(pHandle, DRV8305_C7_GD_CNTRL_ADDR,             &pData->RegRead.cntrl7_gd.all,           DRV8305_C7_GD_CNTRL_ADDR_MASK);                // read DRV8305 control reg 7
    status |= DRV8305ReadSingleReg(pHandle, DRV8305_C9_IC_OPS_ADDR,               &pData->RegRead.cntrl9_IC_ops.all,       DRV8305_C9_IC_OPS_ADDR_MASK);                  // read DRV8305 control reg 9
    status |= DRV8305ReadSingleReg(pHandle, DRV8305_CA_SHUNT_AMP_CNTRL_ADDR,      &pData->RegRead.cntrlA_shunt_amp.all,    DRV8305_CA_SHUNT_AMP_CNTRL_ADDR_MASK);         // read DRV8305 control reg A
    status |= DRV8305ReadSingleReg(pHandle, DRV8305_CB_VREG_CNTRL_ADDR,           &pData->RegRead.cntrlB_Vreg.all,         DRV8305_CB_VREG_CNTRL_ADDR_MASK);              // read DRV8305 control reg B
    status |= DRV8305ReadSingleReg(pHandle, DRV8305_CC_VDS_SNS_CNTRL_ADDR,        &pData->RegRead.cntrlC_Vds_SNS.all,      DRV8305_CC_VDS_SNS_CNTRL_ADDR_MASK);           // read DRV8305 control reg C
    return status;
}

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

    DELAY_US(1);

    if(SPI_SUCCESS != pHandle->pData_DRV8305->pSpi->fTransfer(pHandle->pData_DRV8305->pSpi, w.all, &rData))
    {
        status = DRIVER_FAULT;
    }

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
