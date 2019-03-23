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
* File name: comm_interface.c
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
#if 1//__XXX_xxx__
//#include "xxx_xxx.h"
//#include "xxx_xxx.h"



/*-----------------------ģ���ں궨��-------------------------*/
#define  MSG_BUF_SIZE 			(1024)

#define  MSG_TYPE_REG 			(1)
#define  MSG_TYPE_ACK 			(2)



/*----------------------ģ�����ඨ��--------------------------*/

 
 
typedef struct msg_t
{
    long msg_type;
    char msg_text[MSG_BUF_SIZE];
}MSG_T;


/*----------------------������������--------------------------*/


/*****************************************************************************/
                         /* �������� */
/*****************************************************************************/

/******************************************************************************
* Function:    COMM_InterfaceRegister
* Input:       xxx
* Output:      xxx
* Return:      xxx
* Description: xxxxx
*
*
******************************************************************************/
INT32_T  COMM_InterfaceRegister(void *p_if,INT32_T len)
{
	int qid;
	key_t key;
	MSG_T msg;
	INT32_T comm_id=-1;
	#if 1	//���Դ���
	p_if=malloc(MSG_BUF_SIZE);
	len=MSG_BUF_SIZE;
	memset(p_if,0,len);
	memcpy(p_if,"Please Register Port RS485-1\r\n",len);
	#endif

	printf("%s:%04d\r\n",__func__,__LINE__);
	if ((key = ftok("/", 'a')) == -1)
	{
		perror("ftok");
		return -1;
	}
	 
	/*������Ϣ����*/
	if ((qid = msgget(key, IPC_CREAT|0666)) == -1)
	{
		perror("msgget");
		return -1;
	}

	memcpy(msg.msg_text,p_if,len);
	msg.msg_type=MSG_TYPE_REG;
	
	printf("Snd message from process %ld : %s\r\n", msg.msg_type, msg.msg_text);	
	if ((msgsnd(qid, &msg, strlen(msg.msg_text), 0)) < 0)
	{
		perror("message posted");
		return -1;
	}

	memset(msg.msg_text, 0, MSG_BUF_SIZE);
	msg.msg_type=MSG_TYPE_ACK;
	if (msgrcv(qid, (void*)&msg, MSG_BUF_SIZE, MSG_TYPE_ACK, 0) < 0)   //��ȡ��Ϣ������˭����
	{
		perror("msgrcv");
		exit(1);
	}
	printf("RCV message from process %ld : %s\r\n", msg.msg_type, msg.msg_text);	
	 
	return comm_id;

}

/******************************************************************************
* Function:    COMM_InterfaceUnRegister
* Input:       xxx
* Output:      xxx
* Return:      xxx
* Description: xxxxx
*
*
******************************************************************************/
INT32_T  COMM_InterfaceUnRegister(INT32_T if_id)
{
	printf("%s:%d\r\n",__func__,__LINE__);
	return 1;

}

/******************************************************************************
* Function:    COMM_InterfaceReadDat
* Input:       xxx
* Output:      xxx
* Return:      xxx
* Description: xxxxx
*
*
******************************************************************************/
INT32_T  COMM_InterfaceReadDat(INT32_T if_id,void *pbuf,INT32_T rlen)
{
	printf("%s:%d\r\n",__func__,__LINE__);
	return 1;
}


/******************************************************************************
* Function:    COMM_InterfaceWriteDat
* Input:       xxx
* Output:      xxx
* Return:      xxx
* Description: xxxxx
*
*
******************************************************************************/
INT32_T  COMM_InterfaceWriteDat(INT32_T if_id,void *pbuf,INT32_T wlen)
{
	printf("%s:%d\r\n",__func__,__LINE__);
	return 1;
}


#endif//#if __XXX_xxx__





