/**
 * @file       memory_onchipflash.c
 * @brief 
 * @author     chen yang (yang.chen@dh-robotics.cn)
 * @date       2022-07-29
 * 
 * @copyright  Copyright (c) 2022 by https://www.dh-robotics.com, All Rights Reserved. 
 * 
 * @par        change log:
 * <table>
 * <tr><th>Date             <th>Version    <th>author          <th>Description
 * <tr><td>2022-07-29       <td>1.0        <td>chen yang       <td>����
 * </table>
 */

#include "device_memory.h"
#include "memory_onchipflash.h"
#include <string.h>
// #include "flash_programming_dcsm_c28.h"
#include "F021_F2837xD_C28x.h"

#ifdef __TI_COMPILER_VERSION__
    #if __TI_COMPILER_VERSION__ >= 15009000
        #define ramFuncSection ".TI.ramfunc"
    #else
        #define ramFuncSection "ramfuncs"
    #endif
#endif

#if 1
//
// Globals
//
//#pragma DATA_SECTION(Buffer,"BufferDataSection");
Uint16   Buffer[WORDS_IN_FLASH_BUFFER + 1];
// uint32   *Buffer32 = (uint32 *)Buffer;
//#pragma DATA_SECTION(ReadBuffer,"BufferDataSection");
Uint16   ReadBuffer[WORDS_IN_FLASH_BUFFER + 1];
// uint32   *ReadBuffer32 = (uint32 *)ReadBuffer;
#endif

DATA_ONCHIPFLASH_T Data_OnChipFlash = {
       .MaxDelayCount = 50000,
};

#pragma CODE_SECTION(OnChipFlash_Init, ramFuncSection);
MEMORY_STATUS_T OnChipFlash_Init(MEMORY_T *pHandle)
{
    MEMORY_STATUS_T status = MEMORY_SUCCESS;
    Uint16 BuffCount = 0;

    //
    // Call flash initialization to setup flash wait states.
    // This function must reside in RAM.
    //
    InitFlash();

    pHandle->DataRead.Mdata1    = (int16*)(pHandle->pData_OnChipFlash->RDataBuff + BuffCount);
    pHandle->DataWrite.Mdata1   = (int16*)(pHandle->pData_OnChipFlash->WDataBuff + BuffCount);
    BuffCount += 2;

    pHandle->DataRead.Mdata2    = (int32*)(pHandle->pData_OnChipFlash->RDataBuff + BuffCount);
    pHandle->DataWrite.Mdata2   = (int32*)(pHandle->pData_OnChipFlash->WDataBuff + BuffCount);
    BuffCount += 4;

    pHandle->DataRead.Mdata3    = (int64*)(pHandle->pData_OnChipFlash->RDataBuff + BuffCount);
    pHandle->DataWrite.Mdata3   = (int64*)(pHandle->pData_OnChipFlash->WDataBuff + BuffCount);
    BuffCount += 8;

    pHandle->DataRead.Mdata4    = (Uint16*)(pHandle->pData_OnChipFlash->RDataBuff + BuffCount);
    pHandle->DataWrite.Mdata4   = (Uint16*)(pHandle->pData_OnChipFlash->WDataBuff + BuffCount);
    BuffCount += 2;

    pHandle->DataRead.Mdata5    = (Uint32*)(pHandle->pData_OnChipFlash->RDataBuff + BuffCount);
    pHandle->DataWrite.Mdata5   = (Uint32*)(pHandle->pData_OnChipFlash->WDataBuff + BuffCount);
    BuffCount += 4;

    pHandle->DataRead.Mdata6    = (Uint64*)(pHandle->pData_OnChipFlash->RDataBuff + BuffCount);
    pHandle->DataWrite.Mdata6   = (Uint64*)(pHandle->pData_OnChipFlash->WDataBuff + BuffCount);
    BuffCount += 8;

    pHandle->DataRead.Mdata7    = (float32*)(pHandle->pData_OnChipFlash->RDataBuff + BuffCount);
    pHandle->DataWrite.Mdata7   = (float32*)(pHandle->pData_OnChipFlash->WDataBuff + BuffCount);
    BuffCount += 4;

    pHandle->DataRead.Mdata8    = (float64*)(pHandle->pData_OnChipFlash->RDataBuff + BuffCount);
    pHandle->DataWrite.Mdata8   = (float64*)(pHandle->pData_OnChipFlash->WDataBuff + BuffCount);
    BuffCount += 8;

    return(status);
}

#pragma CODE_SECTION(OnChipFlash_Read, ramFuncSection);
MEMORY_STATUS_T OnChipFlash_Read(MEMORY_T *pHandle)
{
    MEMORY_STATUS_T status = MEMORY_SUCCESS;
   
    volatile uint32 delayCount = 0UL;
    uint32 u32Index = 0UL;
    uint16 i = 0U;
    Fapi_StatusType oReturnCheck;
    volatile Fapi_FlashStatusType oFlashStatus;
    uint32   *Buffer32 = (uint32 *)pHandle->pData_OnChipFlash->RDataBuff;
    uint32   *Buffer32_cach = (uint32 *)pHandle->pData_OnChipFlash->RDataBuff;

    //
    // Grab flash semaphore for Zone1 to enable access to flash registers.
    //
    EALLOW;
    DcsmCommonRegs.FLSEM.all = 0xA501;
    EDIS;

    //
    // Disable ECC.
    //
    EALLOW;
    Flash0EccRegs.ECC_ENABLE.bit.ENABLE = 0x0;

    //
    // This function is required to initialize the Flash API based on system
    // frequency before any other Flash API operation can be performed.
    //
    oReturnCheck = Fapi_initializeAPI(F021_CPU0_BASE_ADDRESS, 120);

    if(oReturnCheck != Fapi_Status_Success)
    {
        return status = MEMORY_FAULT;
    }

    //
    // Fapi_setActiveFlashBank function sets the flash bank and FMC for further
    // flash operations to be performed on the bank.
    //
    oReturnCheck = Fapi_setActiveFlashBank(Fapi_FlashBank0);

    if(oReturnCheck != Fapi_Status_Success)
    {
        return status = MEMORY_FAULT;
    }

    //
    // read buffer into Sector C with ECC.
    //
    for(i=0, u32Index = Bzero_SectorC_start;
       (u32Index < (Bzero_SectorC_start + WORDS_IN_FLASH_BUFFER))
       && (oReturnCheck == Fapi_Status_Success); i+= 8, u32Index+= 8)
    {
        oReturnCheck = Fapi_doMarginRead(
                (uint32 *)u32Index, //uint32 *pu32StartAddress,
                Buffer32_cach, //uint32 *pu32ReadBuffer,
                4,                  //uint32 u32Length,
                Fapi_NormalRead     //Fapi_FlashReadMarginModeType oReadMode
                );
        Buffer32_cach = Buffer32+(i/2);
        if(oReturnCheck != Fapi_Status_Success)
        {
            return status = MEMORY_FAULT;
        }
    }

    //
    // Enable ECC.
    //
    Flash0EccRegs.ECC_ENABLE.bit.ENABLE = 0xA;

    //
    // Release flash semaphore.
    //
    DcsmCommonRegs.FLSEM.all = 0xA500;

    EDIS;

    return(status);
}

#pragma CODE_SECTION(OnChipFlash_Write, ramFuncSection);
MEMORY_STATUS_T OnChipFlash_Write(MEMORY_T *pHandle)
{
    MEMORY_STATUS_T status = MEMORY_SUCCESS;

    volatile uint32 delayCount = 0UL;
    uint32 u32Index = 0UL;
    uint16 i = 0U;
    Fapi_StatusType oReturnCheck;
    volatile Fapi_FlashStatusType oFlashStatus;
    Fapi_FlashStatusWordType oFlashStatusWord;
     uint16   *Buffer16 = (uint16 *)pHandle->pData_OnChipFlash->WDataBuff;
     uint32   *Buffer32 = (uint32 *)pHandle->pData_OnChipFlash->WDataBuff;
    // uint16   *Buffer16_cach = (uint16 *)pHandle->pData_OnChipFlash->WDataBuff;
    // uint32   *Buffer32_cach = (uint32 *)pHandle->pData_OnChipFlash->WDataBuff;
     uint32   *ReadBuffer32 = (uint32 *)pHandle->pData_OnChipFlash->RDataBuff;

//    uint32   *Buffer32 = (uint32 *)Buffer;
//    uint32   *ReadBuffer32 = (uint32 *)ReadBuffer;
    //
    // Grab flash semaphore for Zone1 to enable access to flash registers.
    //
    EALLOW;
    DcsmCommonRegs.FLSEM.all = 0xA501;
    EDIS;

    

    //
    // Call flash initialization to setup flash waitstates.
    // This function must reside in RAM.
    //
    InitFlash();

    //
    // Disable ECC.
    //
    EALLOW;
    Flash0EccRegs.ECC_ENABLE.bit.ENABLE = 0x0;

    //
    // This function is required to initialize the Flash API based on system
    // frequency before any other Flash API operation can be performed.
    //
    oReturnCheck = Fapi_initializeAPI(F021_CPU0_BASE_ADDRESS, 120);

    if(oReturnCheck != Fapi_Status_Success)
    {
        return status = MEMORY_FAULT;
    }

    //
    // Fapi_setActiveFlashBank function sets the flash bank and FMC for further
    // flash operations to be performed on the bank.
    //
    oReturnCheck = Fapi_setActiveFlashBank(Fapi_FlashBank0);

    if(oReturnCheck != Fapi_Status_Success)
    {
        return status = MEMORY_FAULT;
    }

#if 1
    //
    // Erase Sector C.
    //
    oReturnCheck = Fapi_issueAsyncCommandWithAddress(Fapi_EraseSector,
                   (uint32 *)Bzero_SectorC_start);

    //
    // Wait until FSM is done with erase sector operation.
    //
    delayCount = 0;
    while (Fapi_checkFsmForReady() != Fapi_Status_FsmReady)
    {
        delayCount++;
        if(delayCount > pHandle->pData_OnChipFlash->MaxDelayCount)
        {
            return status = MEMORY_FAULT;
        }

    }

    //
    // Verify that Sector C is erased. The erase step itself does verification
    // as it goes. This verify is a second verification that can be done.
    //
    oReturnCheck = Fapi_doBlankCheck((uint32 *)Bzero_SectorC_start,
                   Bzero_16KSector_u32length,
                   &oFlashStatusWord);

    if(oReturnCheck != Fapi_Status_Success)
    {
        return status = MEMORY_FAULT;
    }
#endif


    for(i=0;i<=WORDS_IN_FLASH_BUFFER;i++)
    {
        Buffer[i] = i;
    }

    //
    // Program buffer into Sector C with ECC.
    //
    for(i=0, u32Index = Bzero_SectorC_start;
       (u32Index < (Bzero_SectorC_start + WORDS_IN_FLASH_BUFFER))
       && (oReturnCheck == Fapi_Status_Success); i+= 8, u32Index+= 8)
    {

        oReturnCheck = Fapi_issueProgrammingCommand((uint32 *)u32Index,
                       Buffer16+i,
                       8,
                       0,
                       0,
                       Fapi_AutoEccGeneration);
        //
        // Wait until FSM is done with program operation.
        //
        if(oReturnCheck != Fapi_Status_Success)
        {
            return status = MEMORY_FAULT;
        }

        delayCount = 0;
        while(Fapi_checkFsmForReady() == Fapi_Status_FsmBusy)
        {
            delayCount++;
            if(delayCount > pHandle->pData_OnChipFlash->MaxDelayCount)
            {
                return status = MEMORY_FAULT;
            }
        }

        /*read data*/
        oReturnCheck = Fapi_doMarginRead(
                (uint32 *)u32Index, //uint32 *pu32StartAddress,
                ReadBuffer32+(i/2), //uint32 *pu32ReadBuffer,
                4,                  //uint32 u32Length,
                Fapi_NormalRead     //Fapi_FlashReadMarginModeType oReadMode
                );
        if(oReturnCheck != Fapi_Status_Success)
        {
            return status = MEMORY_FAULT;
        }

        //
        // Read FMSTAT register contents to know the status of FSM after
        // program command for any debug.
        //
        oFlashStatus = Fapi_getFsmStatus();

        //
        // Verify the values programmed. The program step itself does
        // verification as it goes. This verify is a second verification that
        // can be done.
        //
        oReturnCheck = Fapi_doVerify((uint32 *)u32Index,
                       4,
                       Buffer32+(i/2),
                       &oFlashStatusWord);
        if(oReturnCheck != Fapi_Status_Success)
        {
            return status = MEMORY_FAULT;
        }
    }


    //
    // Enable ECC.
    //
    Flash0EccRegs.ECC_ENABLE.bit.ENABLE = 0xA;

    //
    // Release flash semaphore.
    //
    DcsmCommonRegs.FLSEM.all = 0xA500;

    EDIS;

    return status;
}


//
// End of file
//
