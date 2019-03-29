/**************************************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of WAN XING Tech. Co., Ltd.(C) 2020.
* 
*  Copyright (C), 2018-2030, WAN XING Tech. Co., Ltd.
*
***************************************************************************************************
*
* File name: std_macros.h
* -------------------------------------
* 
* Module: xxx 
* -------------------------------------
*
* Project: xxx
* -------------------------------------
*
* Version: V1.0
* -------------------------------------
*
* Description:  This file defines customer-standard common macros for
*                    the project.
* -----------------------------------------------------------------------------
*
* History:
*
* Date                Author             Change Id             Release Description Of Change 
* ---------------------------------------------------------------------------------------
* 2012-12-15           Cris                1st                            created
* ---------------------------------------------------------------------------------------
*
* ---------------------------------------------------------------------------------------
*
**************************************************************************************************/

#ifndef __STD_MACRO_H__
#define __STD_MACRO_H__

#define BIT0               (0x1ul<<0)
#define BIT1               (0x1ul<<1)
#define BIT2               (0x1ul<<2)
#define BIT3               (0x1ul<<3)
#define BIT4               (0x1ul<<4)
#define BIT5               (0x1ul<<5)
#define BIT6               (0x1ul<<6)
#define BIT7               (0x1ul<<7)
#define BIT8               (0x1ul<<8)
#define BIT9               (0x1ul<<9)
#define BIT10              (0x1ul<<10)
#define BIT11              (0x1ul<<11)
#define BIT12              (0x1ul<<12)
#define BIT13              (0x1ul<<13)
#define BIT14              (0x1ul<<14)
#define BIT15              (0x1ul<<15)

#define BIT16              (0x1ul<<16)
#define BIT17              (0x1ul<<17)
#define BIT18              (0x1ul<<18)
#define BIT19              (0x1ul<<19)
#define BIT20              (0x1ul<<20)
#define BIT21              (0x1ul<<21)
#define BIT22              (0x1ul<<22)
#define BIT23              (0x1ul<<23)
#define BIT24              (0x1ul<<24)
#define BIT25              (0x1ul<<25)
#define BIT26              (0x1ul<<26)
#define BIT27              (0x1ul<<27)
#define BIT28              (0x1ul<<28)
#define BIT29              (0x1ul<<29)
#define BIT30              (0x1ul<<30)
#define BIT31              (0x1ul<<31)



#if (__DEBUG_STM32_IN_MDK__)
#define NOP()       __no_operation()
#define EINT()      __enable_interrupt()
#define DINT()      __disable_interrupt()
#define SLEEP()     __sleep()
#define CLR_WDT()   __watchdog_reset()
#else
#define NOP()       __no_operation()
#define EINT()      __enable_interrupt()
#define DINT()      __disable_interrupt()
#define SLEEP()     __sleep()
#define CLR_WDT()   __watchdog_reset()
#endif



#define VALID_FLG			(0x5A)















#endif//#ifndef __STD_MACRO_H__


