/********************************************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of  WAN XING Tech. Co., Ltd.(C) 2012.
*
*  Copyright (C), 2018-2030, WAN XING Tech. Co., Ltd.
*
*********************************************************************************************************
*
* File name: app_modbus_task.h
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
#ifndef __APP_MODBUS_TASK_H__
#define __APP_MODBUS_TASK_H__

#ifdef __cplusplus
extern "C" {
#endif


/*----------------------����ͷ�ļ�----------------------------*/
#include "std_globals.h"
#if __SYS_MODBUS_ENABLE__

//#include "xxx_xxx.h"


/*----------------------�����궨��----------------------------*/
//#define    xxxxxx                (xxxxxxxx)


/*----------------------�����ඨ��----------------------------*/
typedef struct modbus_nvram_t {//nvram data
    unsigned int demo_value;
} MODBUS_NVRAM_T;

typedef struct modbus_gpram_t {//gpram data
	pthread_t thread;
} MODBUS_GPRAM_T;

typedef struct modbus_t {
    MODBUS_NVRAM_T nvram;
    MODBUS_GPRAM_T gpram;
} MODBUS_T;


/*-----------------ģ�����ӿڱ�������-----------------------*/
extern    MODBUS_T modbus;



/*-----------------ģ�����ӿں�������-----------------------*/
extern void* APP_ModbusThread(void *p_arg);


#endif//#if __SYS_MODBUS_ENABLE__

#ifdef __cplusplus
}
#endif
#endif //#ifndef __APP_MODBUS_TASK_H__





