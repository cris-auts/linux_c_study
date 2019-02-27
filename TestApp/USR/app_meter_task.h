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
* File name: app_meter_task.h
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
#ifndef __APP_METER_TASK_H__
#define __APP_METER_TASK_H__

#ifdef __cplusplus
extern "C" {
#endif


/*----------------------����ͷ�ļ�----------------------------*/
#include "std_globals.h"
#if __SYS_METER_ENABLE__

//#include "xxx_xxx.h"


/*----------------------�����궨��----------------------------*/
//#define    xxxxxx                (xxxxxxxx)


/*----------------------�����ඨ��----------------------------*/

typedef struct meter_nvram_t {//nvram data
    unsigned int demo_value;
} METER_NVRAM_T;

typedef struct meter_gpram_t {//gpram data
	pthread_t thread;
} METER_GPRAM_T;

typedef struct meter_t {
    METER_NVRAM_T nvram;
    METER_GPRAM_T gpram;
} METER_T;


/*-----------------ģ�����ӿڱ�������-----------------------*/
extern METER_T meter;


/*-----------------ģ�����ӿں�������-----------------------*/
extern void* APP_MeterThread(void *p_arg);


#endif//#if __SYS_METER_ENABLE__

#ifdef __cplusplus
}
#endif
#endif //#ifndef __APP_METER_TASK_H__





