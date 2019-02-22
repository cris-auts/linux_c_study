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
* File name: app_dlt645_task.h
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
#ifndef __APP_DLT645_TASK_H__
#define __APP_DLT645_TASK_H__

#ifdef __cplusplus
extern "C" {
#endif


/*----------------------公共头文件----------------------------*/
#include "std_globals.h"
#if __SYS_DLT645_ENABLE__

//#include "xxx_xxx.h"


/*----------------------公共宏定义----------------------------*/
//#define    xxxxxx                (xxxxxxxx)


/*----------------------公共类定义----------------------------*/
typedef struct dlt645_nvram_t {//nvram data
    unsigned int demo_value;
} DLT645_NVRAM_T;

typedef struct dlt645_gpram_t {//gpram data
	pthread_t thread;
} DLT645_GPRAM_T;

typedef struct dlt645_t {
    DLT645_NVRAM_T nvram;
    DLT645_GPRAM_T gpram;
} DLT645_T;


/*-----------------模块对外接口变量声明-----------------------*/
extern DLT645_T dlt645;


/*-----------------模块对外接口函数声明-----------------------*/
extern void* APP_Dlt645Thread(void *p_arg);


#endif//#if __SYS_DLT645_ENABLE__

#ifdef __cplusplus
}
#endif
#endif //#ifndef __APP_DLT645_TASK_H__





