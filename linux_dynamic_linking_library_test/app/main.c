#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>      /*文件控制定义*/  
#include <termios.h>    /*PPSIX 终端控制定义*/  
#include <errno.h>      /*错误号定义*/  
#include <sys/types.h>   
#include <sys/stat.h>     
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>   
#include "comm_interface.h"
#include "port.h"





typedef struct reg_map_t {
	UINT32_T if_id;
	UINT32_T port_type;
	UINT8_T  valid_flg;
}REG_MAP_T;



REG_MAP_T reg_map[32];


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
		if (msgrcv(qid, (void*)pmsg, MSG_BUF_SIZE, pmsg->msg_type, IPC_NOWAIT) < 0) 
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
	if ((msgsnd(qid, pmsg, strlen(pmsg->msg_text), 0)) < 0)
	{
		perror("message posted");
		return -1;
	}
	return 0;
}


INT32_T HandleNewMsg(MSG_T* msg)
{
/*
	1.创建对应的管道
	2.更新MAP表格
	3.创建端口线程
*/
	static UINT32_T create_flg=1;
	PORT_CFG_T port_rs485;

	if(create_flg)
	{
		create_flg=0;
		PORT_CreatePortThread(PORT_RS485_1, PORT_RS485, &port_rs485);

	}

	return 0;
}



INT32_T COMM_MsgHandle(void)
{
	int qid;
	MSG_T msg;
	
	if(OpenMsgQ(&qid, "/", 'a')==0)
	{
		memset(&msg,0,sizeof(msg));
		msg.msg_type=MSG_TYPE_REG;
		if(GetNewMsg(qid, &msg, 5000)==0)
		{
			printf("GetNewMsg[%ld]:%s\r\n", msg.msg_type, msg.msg_text);	
			if(strncmp(msg.msg_text, "Please Register Port RS485-1\r\n", strlen("Please Register Port RS485-1\r\n"))==0)
			{
				HandleNewMsg(&msg);
				sleep(5);
				msg.msg_type=MSG_TYPE_ACK;
				memcpy(msg.msg_text,"Register Port RS485-1 Sucessful\r\n",sizeof("Register Port RS485-1 Successful\r\n"));
				PutNewMsg(qid, &msg);
				printf("PutNewMsg[%ld]:%s\r\n", msg.msg_type, msg.msg_text); 
			}
		}
	}

	return 0;
}







int main(int argc, char** argv)
{   
	memset (reg_map,0,sizeof(reg_map));

	g_dev_prm.nvram.debug_log_st.rs485_log=1;

	
	while(1)
	{
		COMM_MsgHandle();
	}

	return 0;
}
 





