/*
 * @Author       : CY [yang.chen@dh-robotics.cn]
 * @Date         : 2022-07-15 17:58:52
 * @LastEditors  : CY [yang.chen@dh-robotics.cn]
 * @LastEditTime : 2022-07-15 18:00:52
 * @FilePath     : \F28379D_temp\28379d_CPU1_temp\06_user\system_setting.h
 * @Description  : 
 * Copyright (c) 2022 by https://www.dh-robotics.com, All Rights Reserved. 
 */


#define  PWM_FREQUENCY          (25.0F)
#define SYSTEM_FREQUENCY        (200000.0F)
#define  INV_PWM_TICKS          ((SYSTEM_FREQUENCY/2.0F)/PWM_FREQUENCY)
#define  INV_PWM_TBPRD              (INV_PWM_TICKS/2.0F)
#define  INV_PWM_HALF_TBPRD         (INV_PWM_TICKS/4.0F)
