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
#include "comm_interface.h"
//#include "xxx_xxx.h"



/*-----------------------模块内宏定义-------------------------*/
#define  MSG_TYPE_REG 			(1)
#define  MSG_TYPE_ACK 			(2)

#define  MSG_RCV_WAIT_CYC 		(1000)



/*----------------------模块内类定义--------------------------*/

 


/*----------------------变量常量定义--------------------------*/


/*****************************************************************************/
                         /* 函数定义 */
/*****************************************************************************/
INT32_T OpenMsgQ(INT32_T* pqid,char* ppath, char id)
{
	key_t key;
	INT32_T err=0;

	if ((key = ftok(ppath, id)) == -1)
	{
		perror("ftok");
		err=-1;
	}

	if ((*pqid = msgget(key, IPC_CREAT|0666)) == -1)
	{
		perror("msgget");
		//printf("qid=%d,line=%d\r\n",*pqid,__LINE__);
		*pqid=0;
		err=-1;
	}
	//printf("qid=%d,line=%d\r\n",*pqid,__LINE__);
	return err;
}

INT32_T CloseMsgQ(INT32_T qid)
{
	INT32_T err=0;
	return err;
}


INT32_T GetNewMsg(INT32_T qid, MSG_T* pmsg, INT32_T wait_ms)
{
	INT32_T wait_cnt=0;

	wait_cnt=wait_ms;
	while(wait_cnt--)
	{
		usleep(1000);
		if (msgrcv(qid, (void*)pmsg, sizeof(MSG_TEXT_T), pmsg->msg_type, IPC_NOWAIT) < 0) 
		{
			//perror("msgrcv");
			return -1;
		}
		else
		{
			
			return 0;
		}
	}
	return -1;

}




INT32_T PutNewMsg(INT32_T qid, MSG_T* pmsg)
{
	if ((msgsnd(qid, pmsg, sizeof(MSG_TEXT_T), 0)) < 0)
	{
		perror("message posted");
		return -1;
	}
	return 0;
}


INT32_T OpenPipe(char* pname, int*ppipe_fd, int mode)
{
	int err=0;
	int pipe_fd = -1;
	int open_mode = mode;
	
    if(access(pname, F_OK) == -1)
    {
        printf ("Create the fifo pipe.\n");
        err = mkfifo(pname, 0777);
        if(err != 0)
        {
            fprintf(stderr, "Could not create fifo %s\n", pname);
			return -1;
        }
    }
	*ppipe_fd = open(pname, open_mode);
	if(*ppipe_fd > 0)
	{
		printf("Process %d fd:%d,err:%d\n", getpid(), *ppipe_fd,err);
		return 0;
	}
	else
	{
		printf("Process %d open %s fail,fd:%d!\n", getpid(), pname,*ppipe_fd);
		return -1;
	}
}



INT32_T ClosePipe(int pipe_fd)
{
	close(pipe_fd);
	return 0;
}


INT32_T ReadPipe(char* pname,char* pbuf, INT32_T rlen)
{
	int err=-1;
	
	int len=0;
 	int pipe_fd = -1;
	
	printf("%s:%d,pipe_fd=%d\r\n",__func__,__LINE__,pipe_fd);
	if(pipe_fd != -1)
	{
		//printf("%s:%d\r\n",__func__,__LINE__);
		len = read(pipe_fd, pbuf, rlen);
		//printf("pipe_fd=%d,read len=%d\r\n",pipe_fd,len);
		return len;
	}
	else
	{
		if(OpenPipe(pname, &pipe_fd,O_RDONLY|O_NONBLOCK)==0)
		{
		
			//printf("%s:%d\r\n",__func__,__LINE__);
			len = read(pipe_fd, pbuf, rlen);
			//printf("pipe_fd=%d,read len=%d\r\n",pipe_fd,len);
			//ClosePipe(pipe_fd);
		}
		//ClosePipe(pipe_fd);
		return len;
	}
}



INT32_T WritePipe(char* pname,char* pbuf,INT32_T wlen)
{	
	int err=-1;
	int len=0;
	int pipe_fd = -1;
	
	if(OpenPipe(pname, &pipe_fd,O_WRONLY|O_NONBLOCK)==0)
	{
		printf("%s:%d,pipe_fd=%d\r\n",__func__,__LINE__,pipe_fd);
		len = write(pipe_fd, pbuf, wlen);
		if((len > 0)&&(len==wlen))
		{
			//printf("WritePipe %d sucess, %d bytes writed\r\n",pipe_fd,len);
			ClosePipe(pipe_fd);
			return len;
		}
	}
	ClosePipe(pipe_fd);
	//printf("WritePipe %d fail, %d bytes writed\r\n",pipe_fd,len);
	return len;
}







/******************************************************************************
* Function:    COMM_InterfaceRegister
* Input:       xxx
* Output:      xxx
* Return:      xxx
* Description: xxxxx
*
*
******************************************************************************/
INT32_T  COMM_InterfaceRegister(void *p_usr_cfg,INT32_T len,INT32_T wait_ms)
{
	int qid;
	key_t key;
	static MSG_T msg;
	int msg_wait_cnt=0;
	INT32_T comm_id=-1;
	

	if ((key = ftok("/", 'b')) == -1)
	{
		perror("ftok");
		return -1;
	}
	 
	/*创建消息队列*/
	if ((qid = msgget(key, IPC_CREAT|0666)) == -1)
	{
		perror("msgget");
		return -1;
	}
	
	msg.msg_type=MSG_TYPE_REG;
	memcpy(&msg.msg_text.reg_text.usr_cfg,p_usr_cfg,len);
	memcpy(&msg.msg_text.reg_text.tips[0],"Please Register Port RS485-1\r\n",MSG_TIPS_SIZE);
	
	printf("Snd message[%ld]: %s\r\n", msg.msg_type, msg.msg_text.reg_text.tips);	
	if ((msgsnd(qid, &msg, sizeof(MSG_TEXT_T), 0)) < 0)
	{
		perror("message posted");
		return -1;
	}


	msg_wait_cnt=wait_ms;
	while(msg_wait_cnt--)
	{
		memset(&msg, 0, sizeof(MSG_T));
		msg.msg_type=MSG_TYPE_ACK;
		usleep(MSG_RCV_WAIT_CYC);
		if (msgrcv(qid, (void*)&msg, sizeof(MSG_TEXT_T), MSG_TYPE_ACK, IPC_NOWAIT) < 0) 
		{
			//perror("msgrcv");
			comm_id=-1;
		}
		else
		{
			printf("RCV message[%ld]: %sch_id=%d\r\n", msg.msg_type, msg.msg_text.ack_text.tips,msg.msg_text.ack_text.ch_id);
			comm_id=msg.msg_text.ack_text.ch_id;
			break;
		}
	}
	/*
	1.更新映射表格
	2.创建对应管道
	*/ 
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
* Function:    COMM_ReadRxFrRxPipe
* Input:       xxx
* Output:      xxx
* Return:      xxx
* Description: xxxxx
*
*
******************************************************************************/
INT32_T  COMM_ReadRxFrRxPipe(INT32_T if_id,void *pbuf,INT32_T rlen)
{
	INT32_T len=0;
	char fifo_name[64];
	int pipe_wfd=-1;
	int pipe_rfd=-1;
	memset(fifo_name,0,sizeof(fifo_name));
	sprintf(fifo_name,"/pipe/rx%05d",if_id);
	if(OpenPipe(fifo_name, &pipe_rfd,O_RDONLY|O_NONBLOCK)==0)
	{
		if(OpenPipe(fifo_name, &pipe_wfd,O_WRONLY|O_NONBLOCK)==0)
		{
			len = read(pipe_rfd, pbuf, rlen);
			ClosePipe(pipe_rfd);
		}
		ClosePipe(pipe_wfd);
	}
	
	if(len >0)
		return len;
	else
		return 0;
}


/******************************************************************************
* Function:    COMM_WriteTxToTxPipe
* Input:       xxx
* Output:      xxx
* Return:      xxx
* Description: xxxxx
*
*
******************************************************************************/
INT32_T  COMM_WriteTxToTxPipe(INT32_T if_id,void *pbuf,INT32_T wlen)
{
	INT32_T len=0;
	char fifo_name[64];
	int pipe_rfd=-1;
	int pipe_wfd=-1;
	memset(fifo_name,0,sizeof(fifo_name));
	sprintf(fifo_name,"/pipe/tx%05d",if_id);
	printf("%s:%d,fifo_name=%s\r\n",fifo_name);
	if(OpenPipe(fifo_name, &pipe_rfd,O_RDONLY|O_NONBLOCK)==0)
	{	
		if(OpenPipe(fifo_name, &pipe_wfd,O_WRONLY|O_NONBLOCK)==0)
		{
			len = write(pipe_wfd, pbuf, wlen);
			ClosePipe(pipe_wfd);
		}
		ClosePipe(pipe_rfd);
	}
	if(len >0)
		return len;
	else
		return 0;
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
INT32_T  COMM_WriteRxToRxPipe(INT32_T if_id,void *pbuf,INT32_T wlen)
{
	INT32_T len=0;
	char fifo_name[64];
	int pipe_rfd=-1;
	int pipe_wfd=-1;
	memset(fifo_name,0,sizeof(fifo_name));
	sprintf(fifo_name,"/pipe/rx%05d",if_id);
	if(OpenPipe(fifo_name, &pipe_rfd,O_RDONLY|O_NONBLOCK)==0)
	{
		if(OpenPipe(fifo_name, &pipe_wfd,O_WRONLY|O_NONBLOCK)==0)
		{
			len = write(pipe_wfd, pbuf, wlen);
			ClosePipe(pipe_wfd);
		}
		ClosePipe(pipe_rfd);
	}
	if(len >0)
		return len;
	else
		return 0;
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
INT32_T  COMM_ReadTxFrTxPipe(INT32_T if_id,void *pbuf,INT32_T rlen)
{
	INT32_T len=0;
	char fifo_name[64];
	int pipe_wfd=-1;
	int pipe_rfd=-1;
	memset(fifo_name,0,sizeof(fifo_name));
	sprintf(fifo_name,"/pipe/tx%05d",if_id);
	
	printf("1func:%s:%d.fifo_name=%s\r\n",__func__,__LINE__,fifo_name);
	if(OpenPipe(fifo_name, &pipe_rfd,O_RDONLY|O_NONBLOCK)==0)
	{
		printf("open write ok\r\n");
		if(OpenPipe(fifo_name, &pipe_wfd,O_WRONLY|O_NONBLOCK)==0)
		{
			printf("open read ok\r\n");
			len = read(pipe_rfd, pbuf, rlen);
			ClosePipe(pipe_rfd);
		}
		ClosePipe(pipe_wfd);
	}
	
	printf("2func:%s:%d.fifo_name=%s\r\n",__func__,__LINE__,fifo_name);
	if(len >0)
		return len;
	else
		return 0;
}


INT32_T  COMM_AppReadDat(INT32_T if_id,void *pbuf,INT32_T rlen)
{
	return COMM_ReadRxFrRxPipe(if_id, pbuf, rlen);
}

INT32_T  COMM_AppWriteDat(INT32_T if_id,void *pbuf,INT32_T wlen)
{
	return COMM_WriteTxToTxPipe(if_id, pbuf, wlen);
}


INT32_T  COMM_CommReadDat(INT32_T if_id,void *pbuf,INT32_T rlen)
{
	return COMM_ReadTxFrTxPipe(if_id, pbuf, rlen);
}

INT32_T  COMM_CommWriteDat(INT32_T if_id,void *pbuf,INT32_T wlen)
{
	return COMM_WriteRxToRxPipe(if_id, pbuf, wlen);
}

#endif//#if __XXX_xxx__





