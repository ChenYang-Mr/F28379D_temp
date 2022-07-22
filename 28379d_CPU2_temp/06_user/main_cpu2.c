//#include "Includes.h"

#include "F2837xD_Ipc_drivers.h"

#include "driverlib.h"
#include "device.h"

#define delay_s(x) SysCtl_delay(((((long double)(x)) / (1.0L /  \
                              (long double)DEVICE_SYSCLK_FREQ)) - 9.0L) / 5.0L)

void main(void)
{
//  Device_init();
//
//    while(1)
//    {
////        GPIO_togglePin(DEVICE_GPIO_PIN_LED1);
//        GPIO_togglePin(DEVICE_GPIO_PIN_LED2);
//        delay_s(2);
//    }
}
