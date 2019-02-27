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
* File name: port_rs485_func.h
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
#ifndef __PORT_RS485_H__
#define __PORT_RS485_H__

#ifdef __cplusplus
extern "C" {
#endif


/*----------------------����ͷ�ļ�----------------------------*/
#include "std_globals.h"
#if __SYS_RS485_ENABLE__

//#include "xxx_xxx.h"


/*----------------------�����궨��----------------------------*/
//#define    xxxxxx                (xxxxxxxx)


/*----------------------�����ඨ��----------------------------*/


/*-----------------ģ�����ӿڱ�������-----------------------*/
//extern    xxxxx;


/*-----------------ģ�����ӿں�������-----------------------*/
extern void* PORT_Rs485Thread(void *p_arg);
extern int PORT_Rs485WrBuf(void *pbuf,int len, int wait_ms);
extern int PORT_Rs485RdBuf(void *pbuf,int len, int wait_ms);

#endif//#if __SYS_RS485_ENABLE__

#ifdef __cplusplus
}
#endif
#endif //#ifndef __PORT_RS485_H__





