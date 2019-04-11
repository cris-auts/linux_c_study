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
* File name: comm_interface.h
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
#if __SYS_COMM_INTERFACE_ENABLE__
#include "dbase.h"


/*----------------------�����궨��----------------------------*/

#define  IPC_ERR_NONE 				(0)
#define  IPC_ERR_OPEN_MSG 			(-1)
#define  IPC_ERR_PUT_MSG 			(-2)
#define  IPC_ERR_GET_MSG 			(-3)




//--------------------------------------------------
#define  COMM_PIPE_CH_SIZE 			(32)
#define  MSG_TIPS_SIZE 				(64)



//��Ϣ����--------------------------------------------
#define  MSG_TYPE_REG_CH_REQ 		(0x01)		//ע��ͨ������
#define  MSG_TYPE_REG_CH_RSP 		(0x02)		//ע��ͨ����Ӧ
#define  MSG_TYPE_GET_ST_REQ 		(0x03)		//��ȡ״̬����
#define  MSG_TYPE_GET_ST_RSP 		(0x04)		//��ȡ״̬��Ӧ

//����/��Ӧ����--------------------------------------------

#define  TEXT_TYPE_REG_CH_IF 		(0x81)		//ע��ͨ����Ϣ
#define  TEXT_TYPE_RSP_CH_ID 		(0x82)		//��Ӧͨ�����
#define  TEXT_TYPE_GET_CH_ST 		(0x83)		//��ȡͨ��״̬
#define  TEXT_TYPE_RSP_CH_ST 		(0x84)		//��Ӧͨ��״̬

/*----------------------�����ඨ��----------------------------*/
typedef struct prm_main
{
	UINT8_T   slaver_run_mode;       //�ֽ������ģʽ
	UINT8_T   slaver_run_ip_index;   //�ֽ������ip����
	TABLE_COMM_PRM_T comm_prm;
}USR_CFG_T;



typedef struct reg_ch_if_text_t{
	UINT32_T  text_type;
	USR_CFG_T usr_cfg;
	CHAR_T	  tips[MSG_TIPS_SIZE];
}REG_CH_IF_TEXT_T;
typedef struct rsp_ch_id_text_t{
	UINT32_T  text_type;
	UINT32_T  ch_id;
	CHAR_T    tips[MSG_TIPS_SIZE];
}RSP_CH_ID_TEXT_T;


typedef struct get_ch_st_text_t{
	UINT32_T text_type;
	UINT32_T ch_id;
	CHAR_T   tips[MSG_TIPS_SIZE];
}GET_CH_ST_TEXT_T;
typedef struct rsp_ch_st_text_t{
	UINT32_T text_type;
	UINT32_T ch_id;
	UINT32_T ch_st;
	CHAR_T   tips[MSG_TIPS_SIZE];
}RSP_CH_ST_TEXT_T;



typedef union msg_text_t
{
	REG_CH_IF_TEXT_T reg_ch_if_text;
	RSP_CH_ID_TEXT_T rsp_ch_id_text;
	GET_CH_ST_TEXT_T get_ch_st_text;
	RSP_CH_ST_TEXT_T rsp_ch_st_text;
}MSG_TEXT_T;



typedef struct msg_t
{
    LONG_T 		msg_type;
    MSG_TEXT_T 	msg_text;
}MSG_T;



/*-----------------ģ�����ӿڱ�������-----------------------*/
//extern    xxxxx;


/*-----------------ģ�����ӿں�������-----------------------*/
extern INT32_T IPC_OpenMsgQ(INT_T *p_qid,	CHAR_T *p_path, CHAR_T id);
extern INT32_T IPC_CloseMsgQ(INT_T qid);
extern INT32_T IPC_GetMsg(INT_T qid, MSG_T *p_msg, UINT32_T wait_ms);
extern INT32_T IPC_PutMsg(INT_T qid, MSG_T *p_msg, UINT32_T wait_ms);

extern void    IPC_Init(void);
extern INT32_T IPC_ChRegister(void *p_usr_cfg,INT32_T len,INT32_T wait_ms,UINT32_T *p_ch_id);
extern INT32_T IPC_ChUnRegister(UINT32_T ch_id);
extern INT32_T IPC_GetChStatus(UINT32_T ch_id, UINT32_T *p_ch_st);
extern INT32_T IPC_AppReadDat(UINT32_T ch_id, void *pbuf, UINT32_T rlen);
extern INT32_T IPC_AppWriteDat(UINT32_T ch_id, void *pbuf, UINT32_T wlen);
extern INT32_T IPC_CommReadDat(UINT32_T ch_id, void *pbuf, UINT32_T rlen);
extern INT32_T IPC_CommWriteDat(UINT32_T ch_id, void *pbuf, UINT32_T wlen);


#endif//#if __SYS_COMM_INTERFACE_ENABLE__

#ifdef __cplusplus
}
#endif
#endif //#ifndef __COMM_INTERFACE_H__











