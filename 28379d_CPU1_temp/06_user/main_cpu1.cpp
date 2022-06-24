#include "Includes.h"
void main(void)
{
//ȷ������ģʽ
#ifdef _STANDALONE
#ifdef _FLASH

    IPCBootCPU2(C1C2_BROM_BOOTMODE_BOOT_FROM_FLASH);
#else

    IPCBootCPU2(C1C2_BROM_BOOTMODE_BOOT_FROM_RAM);
#endif
#endif

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


    while(1)
    {
        GPIO_togglePin(DEVICE_GPIO_PIN_LED1);
        delay_s(1);
    }
}
