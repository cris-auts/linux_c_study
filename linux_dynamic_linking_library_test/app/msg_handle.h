/********************************************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of WAN XING Tech. Co., Ltd.(C) 2020.
*
*  Copyright (C), 2018-2030, WAN XING Tech. Co., Ltd.
*
*********************************************************************************************************
*
* File name: msg_handle.h
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
#ifndef __MSG_HANDLE_H__
#define __MSG_HANDLE_H__

#ifdef __cplusplus
extern "C" {
#endif


/*----------------------公共头文件----------------------------*/
#include "std_globals.h"
#if 1//__XXX_xxx__

//#include "xxx_xxx.h"


/*----------------------公共宏定义----------------------------*/
//#define    xxxxxx                (xxxxxxxx)


/*----------------------公共类定义----------------------------*/
typedef struct ch_port_map_t {
	UINT8_T  valid_flg;
	UINT32_T ch_id; //通道ID
	UINT32_T ch_arg; //通道 参数
	pthread_t ch_thread; //线程ID， 用于查询线程是否存活
}CH_PORT_MAP_T;


/*-----------------模块对外接口变量声明-----------------------*/
extern CH_PORT_MAP_T ch_port_map[32];



/*-----------------模块对外接口函数声明-----------------------*/
//extern    xxxxx;

extern INT32_T MSG_MonitorHandle(void);


#endif//#if 1//__XXX_xxxx__

#ifdef __cplusplus
}
#endif
#endif //#ifndef __MSG_HANDLE_H__





