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
* File name: comm.h
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
#include "msg.h"
#include "dbase.h"


/*----------------------�����궨��----------------------------*/
#define  MSG_TYPE_REG 			(1)
#define  MSG_TYPE_ACK 			(2)

#define  MSG_TIPS_SIZE 			(128)

/*----------------------�����ඨ��----------------------------*/
typedef union msg_text_t
{
	struct reg_text_t{
		PRM_MAIN_T usr_cfg;
		char tips[MSG_TIPS_SIZE];
	}reg_text;
	struct ack_text_t{
		INT32_T ch_id;
		char tips[MSG_TIPS_SIZE];
	}ack_text;
}MSG_TEXT_T;


typedef struct msg_t
{
    long msg_type;
    MSG_TEXT_T msg_text;
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
extern INT32_T  COMM_AppReadDat(INT32_T if_id,void *pbuf,INT32_T rlen);
extern INT32_T  COMM_AppWriteDat(INT32_T if_id,void *pbuf,INT32_T wlen);
extern INT32_T  COMM_CommReadDat(INT32_T if_id,void *pbuf,INT32_T rlen);
extern INT32_T  COMM_CommWriteDat(INT32_T if_id,void *pbuf,INT32_T wlen);


#endif//#if __XXX_xxxx__

#ifdef __cplusplus
}
#endif
#endif //#ifndef __COMM_INTERFACE_H__











