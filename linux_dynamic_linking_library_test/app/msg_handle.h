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


/*----------------------����ͷ�ļ�----------------------------*/
#include "std_globals.h"
#if 1//__XXX_xxx__

//#include "xxx_xxx.h"


/*----------------------�����궨��----------------------------*/
//#define    xxxxxx                (xxxxxxxx)


/*----------------------�����ඨ��----------------------------*/
typedef struct ch_port_map_t {
	UINT8_T  valid_flg;
	UINT32_T ch_id; //ͨ��ID
	UINT32_T ch_arg; //ͨ�� ����
	pthread_t ch_thread; //�߳�ID�� ���ڲ�ѯ�߳��Ƿ���
}CH_PORT_MAP_T;


/*-----------------ģ�����ӿڱ�������-----------------------*/
extern CH_PORT_MAP_T ch_port_map[32];



/*-----------------ģ�����ӿں�������-----------------------*/
//extern    xxxxx;

extern INT32_T MSG_MonitorHandle(void);


#endif//#if 1//__XXX_xxxx__

#ifdef __cplusplus
}
#endif
#endif //#ifndef __MSG_HANDLE_H__





