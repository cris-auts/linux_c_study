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
* File name: xxx_xxx.h
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
#ifndef __COMM_INTERFACE_H__
#define __COMM_INTERFACE_H__

#ifdef __cplusplus
extern "C" {
#endif


/*----------------------����ͷ�ļ�----------------------------*/
#include "std_globals.h"
#if 1//__XXX_xxx__

//#include "xxx_xxx.h"


/*----------------------�����궨��----------------------------*/
#define  MSG_BUF_SIZE 			(1024)

#define  MSG_TYPE_REG 			(1)
#define  MSG_TYPE_ACK 			(2)


/*----------------------�����ඨ��----------------------------*/
typedef struct msg_t
{
    long msg_type;
    char msg_text[MSG_BUF_SIZE];
}MSG_T;


/*-----------------ģ�����ӿڱ�������-----------------------*/
//extern    xxxxx;


/*-----------------ģ�����ӿں�������-----------------------*/
extern INT32_T OpenMsgQ(INT32_T* pqid,char* ppath, char id);
extern INT32_T CloseMsgQ(INT32_T qid);
extern INT32_T GetNewMsg(INT32_T qid, MSG_T* pmsg, INT32_T wait_ms);
extern INT32_T PutNewMsg(INT32_T qid, MSG_T* pmsg);

extern  INT32_T  COMM_InterfaceRegister(void *p_if,INT32_T len,INT32_T wait_ms);
extern  INT32_T  COMM_InterfaceUnRegister(INT32_T if_id);
extern  INT32_T  COMM_InterfaceReadDat(INT32_T if_id,void *pbuf,INT32_T rlen);
extern  INT32_T  COMM_InterfaceWriteDat(INT32_T if_id,void *pbuf,INT32_T wlen);

#endif//#if __XXX_xxxx__

#ifdef __cplusplus
}
#endif
#endif //#ifndef __COMM_INTERFACE_H__











