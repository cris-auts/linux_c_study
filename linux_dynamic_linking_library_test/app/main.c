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
 





