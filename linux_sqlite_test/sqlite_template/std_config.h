/**************************************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of  CRIS Technologies, Inc.
* 
*  Copyright (C), 2010-2015 CRIS Technologies, Inc.
*
***************************************************************************************************
*
* File name: std_config.h
* -------------------------------------
* 
* Module: all 
* -------------------------------------
*
* Project: xxx
* -------------------------------------
*
* Version: V1.0
* -------------------------------------
*
* Description:  This file defines all macros for switch system features and functions
*                     for the project.
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

#ifndef __STD_CONFIG_H__
#define __STD_CONFIG_H__


//-----------------------------------------------------------------------------
#define    __DEBUG_IN_32BIT_SYSTEM__                       (1)

//-----------------------------------------------------------------------------

/****************************************************************************************
                                                 System  Info 
****************************************************************************************/
#define SYS_SOFTWARE_VERSION                            "V1.00.0"		//本地版本号
#define SYS_SOFTWARE_RELEASE_DATE                       "2015-01-01"
#define SYS_HARDWARE_VERSION                            "V1.00.0"
#define SYS_HARDWARE_RELEASE_DATE                       "2015-01-01"

#define SYS_DEVICE_ID                                   "PD-XXX-XXX-XXX"
#define SYS_MANUFACTURER_INFO                           "CRIS Technologies, Inc."

/****************************************************************************************
                                                 User  Info 
****************************************************************************************/
#define USR_SOFTWARE_VERSION                            "V1.00.0"		//用户版本号
#define USR_SOFTWARE_RELEASE_DATE                       "2015-01-01"
#define USR_HARDWARE_VERSION                            "V1.00.0"
#define USR_HARDWARE_RELEASE_DATE                       "2015-01-01"
	
#define USR_DEVICE_ID                                   "PD-XXX-XXX-XXX"
#define USR_MANUFACTURER_INFO                           "CRIS Technologies, Inc."


/****************************************************************************************
                                   System Feature Control
****************************************************************************************/
#define    __SYS_DEBUG_SUPPORT__                        (0)
#define    __SYS_DATABASE_SUPPORT__                     (1)
#define    __SYS_HAL_SUPPORT__                          (0)
#define    __SYS_LED_SUPPORT__                          (0)
#define    __SYS_BEEP_SUPPORT__                         (0)
#define    __SYS_KEY_SUPPORT__                          (0)
#define    __SYS_RTC_SUPPORT__                          (0)
#define    __SYS_NVRAM_SUPPORT__                        (0)
#define    __SYS_FS_SUPPORT__                           (0)
#define    __SYS_USB_SUPPORT__                          (0)
#define    __SYS_GPRS_SUPPORT__                         (0)
#define    __SYS_ETH_SUPPORT__                          (0)
#define    __SYS_MAINT_SUPPORT__                        (0)
#define    __SYS_DLT645_SUPPORT__                       (0)
#define    __SYS_GB101_SUPPORT__                        (0)

/****************************************************************************************
                                System  SubFeature Control
****************************************************************************************/


/****************************************************************************************
                                   App Feature Control
****************************************************************************************/





/****************************************************************************************
                               Middleware Feature  Control
****************************************************************************************/
#if __SYS_DATABASE_SUPPORT__
#define    __SYS_DB_ENABLE__                			(1)	//Added By Cris@20190214
#define    __DB_SQLITE3_ENABLE__                		(1)	//Added By Cris@20190214
#endif




/****************************************************************************************
                                Advanced Driver Feature Control
****************************************************************************************/
//LED MODULE-------------------------------------------------------------------
#if __SYS_LED_SUPPORT__
#define    __DRV_LED_ENABLE__                           (1)
#define    __DRV_LED_DEBUG__                            (1)
#endif

//BEEP MODULE------------------------------------------------------------------
#if __SYS_BEEP_SUPPORT__
#define    __DRV_BEEP_ENABLE__                          (1)
#define    __DRV_BEEP_DEBUG__                           (1)
#endif

//KEY MODULE-------------------------------------------------------------------
#define    __DRV_KEY_ENABLE__                           (0)
#define    __DRV_KEY_DEBUG__                            (0)
#define    __DRV_KEY_LEVEL_REVERSE__                    (0)


//LCD MODULE-------------------------------------------------------------------
#define    __DRV_LCD_XXXX_ENABLE__                      (0)
#define    __DRV_LCD_XXXX_DEBUG__                       (0)

//FLASH MODULE-------------------------------------------------------------------
#if (__MDW_NVRAM_SPI_FLASH__||__MDW_FATFS_SPIFLASH_ENABLE__)
#define    __DRV_SPI_FLASH_ENABLE__                     (__DRV_SPI_FLASH_W25QXX_ENABLE__)
#define    __DRV_SPI_FLASH_DEBUG__                          (1)
#define    __DRV_SPI_FLASH_W25QXX_ENABLE__                  (1)
#endif

//RTC MODULE-------------------------------------------------------------------
#if __SYS_RTC_SUPPORT__
#define    __DRV_RTC_ENABLE__                           (__DRV_RTC_STM32_ENABLE__)
#define    __DRV_RTC_DEBUG__                            (1)
#define    __DRV_RTC_STM32_ENABLE__                     (1)
#endif

//USB MODULE-------------------------------------------------------------------
#if __SYS_USB_SUPPORT__
#define    __DRV_SYS_CLK_192M_ENABLE__                  (1)
#define    __DRV_USB_ENABLE__                           (1)
#define    __DRV_USB_DEBUG__                            (1)
#endif

/****************************************************************************************
                                    Basic Driver Feature Control
****************************************************************************************/

//TIMER MODULE-----------------------------------------------------------------
#if __SYS_OS_SUPPORT__
#define    __DRV_SYSTICK_ENABLE__                       (1)
#define    __DRV_SYSTICK_DEBUG__                        (1)
#endif
#define    __DRV_TIMER1_ENABLE__                        (0)
#define    __DRV_TIMER1_DEBUG__                         (0)

//UART MODULE-----------------------------------------------------------------
#define    __DRV_UART_ENABLE__                          (__DRV_UART0_ENABLE__||__DRV_UART1_ENABLE__)

#define    __DRV_UART0_ENABLE__                         (0)
#define    __DRV_UART0_DEBUG__                          (0)
#if __SYS_PRINT_UART1__
#define    __DRV_UART1_ENABLE__                         (1)
#define    __DRV_UART1_DEBUG__                          (0)
#endif


//SPI MODULE-------------------------------------------------------------------
#define    __DRV_SPI_ENABLE__                           (__DRV_SPI5_ENABLE__)
#if __DRV_SPI_FLASH_ENABLE__
#define    __DRV_SPI5_ENABLE__                          (1)
#define    __DRV_SPI5_DEBUG__                           (1)
#endif



/*************************************************************************************************/
#endif//#ifndef __STD_CONFIG_H__

