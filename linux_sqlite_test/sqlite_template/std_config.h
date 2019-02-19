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
#define SYS_SOFTWARE_RELEASE_TIME                       "17:00:00"

#define SYS_HARDWARE_VERSION                            "V1.00.0"
#define SYS_HARDWARE_RELEASE_DATE                       "2015-01-01"
#define SYS_HARDWARE_RELEASE_TIME                       "17:00:00"

#define SYS_DEVICE_ID                                   "PD-XXX-XXX-XXX"
#define SYS_MANUFACTURER_INFO                           "WAN XING Tech. Co., Ltd."


/****************************************************************************************
                                                 User  Info 
****************************************************************************************/
#define USR_SOFTWARE_VERSION                            "V1.00.0"		//用户版本号
#define USR_SOFTWARE_RELEASE_DATE                       "2015-01-01"
#define USR_SOFTWARE_RELEASE_TIME                       "17:00:00"

#define USR_HARDWARE_VERSION                            "V1.00.0"
#define USR_HARDWARE_RELEASE_DATE                       "2015-01-01"
#define USR_HARDWARE_RELEASE_TIME                       "17:00:00"
	
#define USR_DEVICE_ID                                   "PD-XXX-XXX-XXX"
#define USR_MANUFACTURER_INFO                           " WAN XING Tech. Co., Ltd."


/****************************************************************************************
                                   System Feature Control
****************************************************************************************/
#define    __SYS_DEBUG_SUPPORT__                        (1)	//Added By Cris@20190218
#define    __SYS_FUNCS_SUPPORT__                        (1)	//Added By Cris@20190218
#define    __SYS_DBASE_SUPPORT__                     	(1)	//Added By Cris@20190218
#define    __SYS_MODBUS_SUPPORT__                       (1)	//Added By Cris@20190218
#define    __SYS_DLT645_SUPPORT__                       (1)	//Added By Cris@20190218
#define    __SYS_METER_SUPPORT__                       	(1)	//Added By Cris@20190218



/****************************************************************************************
                               Middleware Feature  Control
****************************************************************************************/
#if __SYS_DEBUG_SUPPORT__
#define    __STD_DEBUG_ENABLE__                			(1)	//Added By Cris@20190218
#define    __SYS_DEBUG_LOG_ENABLE__                		(1)	//Added By Cris@20190218
#define		__SYS_PRINT_UART1__							(0)
#endif

#if __SYS_FUNCS_SUPPORT__
#define    __STD_FUNCS_ENABLE__                			(1)	//Added By Cris@20190218
#define    __SYS_FUNCS_LOG_ENABLE__                		(1)	//Added By Cris@20190218
#endif

#if __SYS_DBASE_SUPPORT__
#define    __SYS_DBASE_ENABLE__                			(1)	//Added By Cris@20190218
#define    __SYS_DBASE_LOG_ENABLE__                		(1)	//Added By Cris@20190218
#define    __DBASE_SQLITE3_ENABLE__                		(1)	//Added By Cris@20190218
#endif

#if __SYS_MODBUS_SUPPORT__
#define    __SYS_MODBUS_ENABLE__                		(1)	//Added By Cris@20190218
#define    __SYS_MODBUS_LOG_ENABLE__                	(1)	//Added By Cris@20190218
#endif

#if __SYS_DLT645_SUPPORT__
#define    __SYS_DLT645_ENABLE__                		(0)	//Added By Cris@20190218
#define    __SYS_DLT645_LOG_ENABLE__                	(0)	//Added By Cris@20190218
#endif

#if __SYS_METER_SUPPORT__
#define    __SYS_METER_ENABLE__                			(0)	//Added By Cris@20190218
#define    __SYS_METER_LOG_ENABLE__                		(0)	//Added By Cris@20190218
#endif


/*************************************************************************************************/
#endif//#ifndef __STD_CONFIG_H__

