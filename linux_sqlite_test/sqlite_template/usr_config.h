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
#ifndef __USR_CONFIG_H__
#define __USR_CONFIG_H__

#define USR_MASTER						(0x01)	/*MASTER*/
#define USR_ANHUI						(0x02)	/*安徽*/
#define USR_JIANGSU						(0x03)	/*江苏*/
#define USR_STATEGRID					(0xFF)	/*国网*/


#define USR_ID							(USR_MASTER)


#if (USR_ID == USR_MASTER)
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
                                              User Feature Control
****************************************************************************************/
#define    __USR_DEBUG_SUPPORT__                        (1)
#define    __USR_OS_SUPPORT__                           (1)
#define    __USR_HAL_SUPPORT__                          (0)
#define    __USR_LED_SUPPORT__                          (1)
#define    __USR_BEEP_SUPPORT__                         (1)
#define    __USR_KEY_SUPPORT__                          (1)
#define    __USR_RTC_SUPPORT__                          (1)
#define    __USR_NVRAM_SUPPORT__                        (1)
#define    __USR_FS_SUPPORT__                           (1)
#define    __USR_USB_SUPPORT__                          (1)
#define    __USR_GPRS_SUPPORT__                         (0)
#define    __USR_ETH_SUPPORT__                          (0)
#define    __USR_MAINT_SUPPORT__                        (0)
#define    __USR_DLT645_SUPPORT__                       (0)
#define    __USR_GB101_SUPPORT__                        (0)
/****************************************************************************************
                                               User  SubFeature Control
****************************************************************************************/
#define    __USR_LED_FLICKER_CYC_500MS__                (1)		//Added By Cris@20181115


/****************************************************************************************
                                               User Bug  Fixed Control
****************************************************************************************/
#define    __BUGFIX_XXXXX__                          	(1)     //Fixed By Cris@20181115 




/****************************************************************************************
-------------------------------------------END------------------------------------------
****************************************************************************************/

#elif (USR_ID == USR_ANHUI)
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
                                              User Feature Control
****************************************************************************************/
#define    __USR_DEBUG_SUPPORT__                        (1)
#define    __USR_OS_SUPPORT__                           (1)
#define    __USR_HAL_SUPPORT__                          (0)
#define    __USR_LED_SUPPORT__                          (1)
#define    __USR_BEEP_SUPPORT__                         (1)
#define    __USR_KEY_SUPPORT__                          (1)
#define    __USR_RTC_SUPPORT__                          (1)
#define    __USR_NVRAM_SUPPORT__                        (1)
#define    __USR_FS_SUPPORT__                           (1)
#define    __USR_USB_SUPPORT__                          (1)
#define    __USR_GPRS_SUPPORT__                         (0)
#define    __USR_ETH_SUPPORT__                          (0)
#define    __USR_MAINT_SUPPORT__                        (0)
#define    __USR_DLT645_SUPPORT__                       (0)
#define    __USR_GB101_SUPPORT__                        (0)
/****************************************************************************************
                                               User  Function Control
****************************************************************************************/
#define    __SYS_LED_FLICKER_CYC__                      (1)		//Added By Cris@20181115


/****************************************************************************************
                                               User Bug  Fixed Control
****************************************************************************************/
#define    __BUGFIX_XXXXX__                          	(1)     //Fixed By Cris@20181115 




/****************************************************************************************
-------------------------------------------END------------------------------------------
****************************************************************************************/
#elif (USR_ID == USR_JIANGSU)
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

/****************************************************************************************
											  User Feature Control
****************************************************************************************/
#define    __USR_DEBUG_SUPPORT__                        (1)
#define    __USR_OS_SUPPORT__                           (1)
#define    __USR_HAL_SUPPORT__                          (0)
#define    __USR_LED_SUPPORT__                          (1)
#define    __USR_BEEP_SUPPORT__                         (1)
#define    __USR_KEY_SUPPORT__                          (1)
#define    __USR_RTC_SUPPORT__                          (1)
#define    __USR_NVRAM_SUPPORT__                        (1)
#define    __USR_FS_SUPPORT__                           (1)
#define    __USR_USB_SUPPORT__                          (1)
#define    __USR_GPRS_SUPPORT__                         (0)
#define    __USR_ETH_SUPPORT__                          (0)
#define    __USR_MAINT_SUPPORT__                        (0)
#define    __USR_DLT645_SUPPORT__                       (0)
#define    __USR_GB101_SUPPORT__                        (0)
/****************************************************************************************
											   User  Function Control
****************************************************************************************/
#define    __SYS_LED_FLICKER_CYC__                      (1)		//Added By Cris@20181115
	

/****************************************************************************************
											   User Bug	Fixed Control
****************************************************************************************/
#define    __BUGFIX_XXXXX__                          	(1)     //Fixed By Cris@20181115 
	
	
	
	
/****************************************************************************************
-------------------------------------------END------------------------------------------
****************************************************************************************/


#elif (USR_ID == USR_STATEGRID)
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

/****************************************************************************************
                                             User User Feature Control
****************************************************************************************/
#define    __USR_DEBUG_SUPPORT__                        (1)
#define    __USR_OS_SUPPORT__                           (1)
#define    __USR_HAL_SUPPORT__                          (0)
#define    __USR_LED_SUPPORT__                          (1)
#define    __USR_BEEP_SUPPORT__                         (1)
#define    __USR_KEY_SUPPORT__                          (1)
#define    __USR_RTC_SUPPORT__                          (1)
#define    __USR_NVRAM_SUPPORT__                        (1)
#define    __USR_FS_SUPPORT__                           (1)
#define    __USR_USB_SUPPORT__                          (1)
#define    __USR_GPRS_SUPPORT__                         (0)
#define    __USR_ETH_SUPPORT__                          (0)
#define    __USR_MAINT_SUPPORT__                        (0)
#define    __USR_DLT645_SUPPORT__                       (0)
#define    __USR_GB101_SUPPORT__                        (0)
/****************************************************************************************
                                               User Function Control
****************************************************************************************/
#define    __SYS_LED_FLICKER_CYC__                      (1)		//Added By Cris@20181115


/****************************************************************************************
                                               User Bug  Fixed Control
****************************************************************************************/
#define    __BUGFIX_XXXXX__                          	(1)     //Fixed By Cris@20181115 




/****************************************************************************************
-------------------------------------------END------------------------------------------
****************************************************************************************/

#else
#error "No user selectde, please define USR_ID!"
#endif


#endif//__USR_CONFIG_H__

