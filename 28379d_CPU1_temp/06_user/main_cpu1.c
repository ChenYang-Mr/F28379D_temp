//#include "Includes.h"


//#include <F2837xD_device.h>
#include "F2837xD_Ipc_drivers.h"

#include "driverlib.h"
#include "device.h"
#include "device_driver.h"

#define delay_s(x) SysCtl_delay(((((long double)(x)) / (1.0L /  \
                              (long double)DEVICE_SYSCLK_FREQ)) - 9.0L) / 5.0L)
void main(void)
{
//确定运行模式
#ifdef _STANDALONE
#ifdef _FLASH

    IPCBootCPU2(C1C2_BROM_BOOTMODE_BOOT_FROM_FLASH);
#else

    IPCBootCPU2(C1C2_BROM_BOOTMODE_BOOT_FROM_RAM);
#endif
#endif

    //设备初始化
    Device_init();
    //GPIO初始化
    Device_initGPIO();

    Interrupt_initModule();
    Interrupt_initVectorTable();
    //开启总中断
    Interrupt_enableMaster();

    GPIO_setPinConfig(DEVICE_GPIO_CFG_LED1);
    GPIO_setMasterCore(DEVICE_GPIO_PIN_LED1, GPIO_CORE_CPU1);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_LED1, GPIO_PIN_TYPE_STD);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_LED1, GPIO_DIR_MODE_OUT);

    GPIO_setPinConfig(DEVICE_GPIO_CFG_LED2);
    GPIO_setMasterCore(DEVICE_GPIO_PIN_LED2, GPIO_CORE_CPU2);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_LED2, GPIO_PIN_TYPE_STD);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_LED2, GPIO_DIR_MODE_OUT);

    DRIVER.fInit(&DRIVER);
    DRIVER.fReadStatusReg(&DRIVER);

    while(1)
    {
        GPIO_togglePin(DEVICE_GPIO_PIN_LED1);
//        GPIO_togglePin(DEVICE_GPIO_PIN_LED2);
        delay_s(1);
    }
}
