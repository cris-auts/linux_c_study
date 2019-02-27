/********************************************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of  WAN XING Tech. Co., Ltd.(C) 2012.
*
*  Copyright (C), 2010-2020, WAN XING Tech. Co., Ltd.
*
*********************************************************************************************************
*
* File name: nvram.h
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
* Description:  xxxxxxxxxxxxxxxxxxxxxxxx
*
* ------------------------------------------------------------------------
*
* History:
*
* Date                Author             Change Id             Release Description Of Change
* ------------------------------------------------------------------------------------------------------
*
*
* ------------------------------------------------------------------------------------------------------
*
*
* ------------------------------------------------------------------------------------------------------
*
* Others:
*
********************************************************************************************************/
#ifndef __NVRAM_H__
#define __NVRAM_H__

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------公共头文件----------------------------*/
#include "std_globals.h"
#if __SYS_NVRAM_ENABLE__
/*----------------------公共宏定义----------------------------*/

#define NVRAM_HANDLE_OK					(0x00)
#define NVRAM_VERIFY_ERR				(0x01)
#define NVRAM_INVAILD_ERR				(0x02)
#define NVRAM_TIMEOUT_ERR				(0x03)
#define NVRAM_READ_ERR					(0x04)
#define NVRAM_WRITE_ERR					(0x05)
#define NVRAM_UNKNOWN_ERR				(0xFF)


/*----------------------公共类定义----------------------------*/
typedef enum nvram_id_t
{
	NVRAM_DEV_PRM_ID,
	NVRAM_DEV_DAT_ID,
	NVRAM_USR_PRM_ID,
	NVRAM_USR_DAT_ID,
	NVRAM_RUN_PRM_ID,
	NVRAM_RUN_DAT_ID,
	#if __SYS_MODBUS_ENABLE__
	NVRAM_MODBUS_ID,
	#endif
	#if __SYS_DLT645_ENABLE__
	NVRAM_DLT645_ID,
	#endif
	#if __SYS_METER_ENABLE__
	NVRAM_METER_ID,
	#endif
	NVRAM_MAX_ID,

}NVRAM_ID_T;


/*-----------------模块对外接口变量声明-----------------------*/
//extern    xxxxx;


/*-----------------模块对外接口函数声明-----------------------*/
extern INT16_T NVRAM_Init(void);
extern INT16_T NVRAM_Load(void);
extern INT16_T NVRAM_Read(NVRAM_ID_T id,UINT8_T unit,void* pbuf);
extern INT16_T NVRAM_Write(NVRAM_ID_T id,UINT8_T unit,void* pbuf);
#endif//#if __SYS_NVRAM_ENABLE__

#ifdef __cplusplus
}
#endif
#endif //#ifndef __NVRAM_H__

