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
* File name: msg_handle.c
* -------------------------------------
*
* Module: xxx
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
* Date                   Author             Change Id             Release Description Of Change
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
/*------------------------------------------------------------------*/
#include "std_globals.h"
//#if __XXX_xxx__
#include "port.h"
#include "dbase.h"
#include "msg.h"



/*-----------------------ģ���ں궨��-------------------------*/
//#define    xxxxxx              (xxxxxxxx)
#define CH_PORT_MAP_SIZE		(32)



/*----------------------ģ�����ඨ��--------------------------*/


typedef struct ch_port_map_t {
	UINT8_T  	valid_flg;
	UINT32_T 	ch_id; //ͨ��ID
	PORT_T 		*p_port; //�߼��˿ڲ���
}CH_PORT_MAP_T;


/*----------------------������������--------------------------*/


CH_PORT_MAP_T ch_port_map[CH_PORT_MAP_SIZE];
PORT_DEV_CFG_T *p_dev_cfg_map;






/*****************************************************************************/
                         /* �������� */
/*****************************************************************************/
/******************************************************************************
* Function:    MSG_ChkSameItemCfgs
* Input:       xxx
* Output:      xxx
* Return:      ���������ͬ���򷵻�TRUE��������ͬ����ͨ��p_map_tab_id����
* Description: ��������Ƿ��Ѿ�����Ҫע�����
*
*
******************************************************************************/
INT32_T MSG_ChkSameItemCfgs(PORT_USR_CFG_T *p_usr_cfg, PORT_T *p_port)
{
	/*
		���˹�Լ���Ͳ��У������Ķ�Ҫ��
	*/

	PRTC_TYPE_T usr_port_prtc;
	usr_port_prtc = p_usr_cfg->comm_prm.prtc_type;
	p_usr_cfg->comm_prm.prtc_type = p_port->port_cfg.usr_cfg.comm_prm.prtc_type;

	
	if(memcmp(p_usr_cfg,&(p_port->port_cfg.usr_cfg),sizeof(PORT_USR_CFG_T)) == 0)
	{
		p_usr_cfg->comm_prm.prtc_type=usr_port_prtc;
		return 1;
	}
	else
	{
		p_usr_cfg->comm_prm.prtc_type=usr_port_prtc;
		return 0;
	}
}


/******************************************************************************
* Function:    MSG_ChkSameItemCfgs
* Input:       xxx
* Output:      xxx
* Return:      ���������ͬ���򷵻�TRUE��������ͬ����ͨ��p_map_tab_id����
* Description: ��������Ƿ��Ѿ�����Ҫע�����
*
*
******************************************************************************/
INT32_T MSG_ChkSameItemPrtcCfgs(PORT_USR_CFG_T* p_usr_cfg, PORT_T *p_port)
{
	/*����Լ�Ƿ���ͬ*/
	if(p_usr_cfg->comm_prm.prtc_type == p_port->port_cfg.usr_cfg.comm_prm.prtc_type)
		return 1;
	else
		return 0;
}


/******************************************************************************
* Function:    MSG_ChkSameMapTabItems
* Input:       xxx
* Output:      xxx
* Return:      ���������ͬ���򷵻�TRUE��������ͬ����ͨ��p_map_tab_id����
* Description: ��������Ƿ��Ѿ�����Ҫע�����
*
*
******************************************************************************/
INT32_T MSG_ChkSameMapTabItems(PORT_USR_CFG_T* p_usr_cfg,INT32_T *p_map_tab_idx)
{

	UINT32_T i=0;
	for(i=0;i<CH_PORT_MAP_SIZE;i++)
	{
		if(ch_port_map[i].valid_flg==VALID_FLG)
		{
			if(MSG_ChkSameItemCfgs(p_usr_cfg, ch_port_map[i].p_port))
			{
				*p_map_tab_idx=i;
				return 1;
			}
		}
	}
	*p_map_tab_idx=0xffff;
	return 0;
}

/******************************************************************************
* Function:    MSG_InsertMapTabItem
* Input:       xxx
* Output:      xxx
* Return:      xxx
* Description: xxxxx
*
*
******************************************************************************/
INT32_T MSG_InsertMapTabItem(INT32_T map_tab_idx,PORT_T*p_port)
{
	if(ch_port_map[map_tab_idx].valid_flg == VALID_FLG)
		return -1;
	ch_port_map[map_tab_idx].valid_flg = VALID_FLG;
	ch_port_map[map_tab_idx].ch_id = map_tab_idx;
	ch_port_map[map_tab_idx].p_port = p_port;
	return 0;
}




/******************************************************************************
* Function:    MSG_DeleteMapTabItem
* Input:       xxx
* Output:      xxx
* Return:      xxx
* Description: xxxxx
*
*
******************************************************************************/
INT32_T MSG_DeleteMapTabItem(MSG_T* p_msg, INT32_T p_map_tab_id)
{

	return 0;
}




/******************************************************************************
* Function:    MSG_GenMapTabId
* Input:       xxx
* Output:      xxx
* Return:      xxx
* Description: xxxxx
*
*
******************************************************************************/
INT32_T MSG_GenMapTabId(INT32_T*p_map_tab_idx)
{
	UINT32_T i=0;
	for(i=0;i<CH_PORT_MAP_SIZE;i++)
	{
		if(ch_port_map[i].valid_flg!=VALID_FLG)
		{
			*p_map_tab_idx=i;
			return 0;
		}
	}
	*p_map_tab_idx=0xffff;
	
	return -1;
}



/******************************************************************************
* Function:    HandleNewMsg
* Input:       xxx
* Output:      xxx
* Return:      xxx
* Description: xxxxx
*
*
******************************************************************************/
INT32_T MSG_HandleNewMsg(MSG_T* p_msg,INT32_T *p_ch_id)
{
	INT32_T i=0;
	INT32_T err=0;
	INT32_T map_tab_idx;
	INT32_T map_tab_new_idx;
	PORT_T  *p_port=NULL;
	//static INT32_T prtc_cnt=0;
	PORT_USR_CFG_T *p_usr_cfg=(PORT_USR_CFG_T*)&(p_msg->msg_text.reg_text.usr_cfg);
	#if 0//���Դ���
	p_usr_cfg->comm_prm.comm_port=COMM_RS485_1;
	p_usr_cfg->comm_prm.prtc_type=prtc_cnt++;
	#endif
	if(MSG_ChkSameMapTabItems(p_usr_cfg,&map_tab_idx))
	{// ������ͬ�Ĳ���
		if(MSG_ChkSameItemPrtcCfgs(p_usr_cfg,ch_port_map[map_tab_idx].p_port))
		{//��ȫ��ͬ���ظ�ע�ᣬ���ر���е�ͨ��ID
			*p_ch_id=ch_port_map[map_tab_idx].ch_id;
			return 0;
		}
		else
		{//����Լ��ͬ��ͬһ���߼��˿��£���ͬ�Ĺ�Լ����Ҫ�½�һ��ͨ��ID�������µ��˿��̲߳����С�
			err=MSG_GenMapTabId(&map_tab_new_idx);
			if(err==0)
			{
				for(i=0;i<PORT_MULTI_CH_MAX;i++)
				{
					if(ch_port_map[map_tab_idx].p_port->prtc_tab[i].valid_flg != VALID_FLG)
					{
						ch_port_map[map_tab_idx].p_port->prtc_tab[i].valid_flg = VALID_FLG;
						ch_port_map[map_tab_idx].p_port->prtc_tab[i].prtc=(UINT32_T)p_usr_cfg->comm_prm.prtc_type;
						ch_port_map[map_tab_idx].p_port->prtc_tab[i].ch_id=map_tab_new_idx;
						MSG_InsertMapTabItem(map_tab_new_idx,ch_port_map[map_tab_idx].p_port);
						*p_ch_id=map_tab_new_idx;
						return 0;
					}
				}
				return -1;
			}
			return -1;
		}	
	}
	else
	{//����Լ�⣬���ڲ�ͬ��������Ҫ�����µ��̺߳�ͨ��ID
	
		err=MSG_GenMapTabId(&map_tab_new_idx);
		if(err==0)
		{
			p_port=(PORT_T *)malloc(sizeof(PORT_T));
			if(p_port == NULL)
			{
				printf("Malloc PORT failed!\r\n");
			}
			memset(p_port,0,sizeof(PORT_T));
			if(PORT_InitPortInfo(p_port,map_tab_new_idx,p_dev_cfg_map,p_usr_cfg)==0)
			{
				if(PORT_CreatePortThread(p_port))
				{
					printf("Create port thread failed!\r\n");
					free(p_port);
					p_port=NULL;
					return -1;
				}
			}
			else
			{
				printf("PORT_InitPortInfo failed!\r\n");
				if(p_port->p_port_rx_buf != NULL)
				{
					free(p_port->p_port_rx_buf);
					p_port->p_port_rx_buf=NULL;
				}
				if(p_port->p_port_tx_buf != NULL)
				{
					free(p_port->p_port_tx_buf);
					p_port->p_port_tx_buf=NULL;
				}
				free(p_port);
				p_port=NULL;
				return -1;
			}

			if(MSG_InsertMapTabItem(map_tab_new_idx,p_port))
			{
				printf("MSG_InsertMapTabItem failed!\r\n");
				return -1;
			}else
			{
				*p_ch_id=map_tab_new_idx;
				return 0;
			}
		}
		return -1;
	}
}




/******************************************************************************
* Function:    MSG_MonitorHandle
* Input:       xxx
* Output:      xxx
* Return:      xxx
* Description: xxxxx
*
*
******************************************************************************/
INT32_T MSG_MonitorHandle(void)
{
	int qid;
	static MSG_T msg;
	INT32_T ch_id;
	if(OpenMsgQ(&qid, "/", 'b')==0)
	{
		memset(&msg,0,sizeof(msg));
		msg.msg_type=MSG_TYPE_REG;
		if(GetNewMsg(qid, &msg, 5000)==0)
		{
			printf("GetNewMsg[%ld]:%s\r\n", msg.msg_type, msg.msg_text.reg_text.tips);	
			if(strncmp(msg.msg_text.reg_text.tips, "Please Register Port\r\n", strlen("Please Register Port\r\n"))==0)
			{
				if(MSG_HandleNewMsg(&msg,&ch_id)==0)
				{
					sleep(1);
					msg.msg_type=MSG_TYPE_ACK;
					msg.msg_text.ack_text.ch_id=ch_id;
					memcpy(msg.msg_text.ack_text.tips,"Register Port Sucessful\r\n",sizeof("Register Port Sucessful\r\n"));
					PutNewMsg(qid, &msg);
					printf("PutNewMsg[%ld]:%sch_id=%d\r\n", msg.msg_type, msg.msg_text.ack_text.tips,ch_id); 

				}
				else
				{
					sleep(1);
					msg.msg_type=MSG_TYPE_ACK;
					msg.msg_text.ack_text.ch_id=-1;
					memcpy(msg.msg_text.ack_text.tips,"Register Port RS485-1 Failed!\r\n",sizeof("Register Port RS485-1 Failed!\r\n"));
					PutNewMsg(qid, &msg);
					printf("PutNewMsg[%ld]:%s\r\n", msg.msg_type, msg.msg_text.ack_text.tips); 
				}
			}
		}
	}

	return 0;
}





//#endif//#if __XXX_xxx__





