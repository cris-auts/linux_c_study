#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>      /*�ļ����ƶ���*/  
#include <termios.h>    /*PPSIX �ն˿��ƶ���*/  
#include <errno.h>      /*����Ŷ���*/  
#include <sys/types.h>   
#include <sys/stat.h>     
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>   
#include "comm_interface.h"


#define  BUFFER_SIZE		1024
#define  MSG_TYPE_REG 			(1)
#define  MSG_TYPE_ACK 			(2)
 
struct message
{
	long msg_type;
	char msg_text[BUFFER_SIZE];
};



int main(int argc, char** argv)
{   

	int qid;
	key_t key;
	struct message msg;
	
	/*���ݲ�ͬ��·���͹ؼ���ʾ������׼��key*/
	if ((key = ftok("/", 'a')) == -1)
	{
		perror("ftok");
		exit(1);
	}
	
	/*������Ϣ����*/
	if ((qid = msgget(key, IPC_CREAT|0666)) == -1)
	{
		perror("msgget");
		exit(1);
	}
	printf("Open queue %d\n", qid);
	while(1)
	{
		do
		{
			/*��ȡ��Ϣ����*/
			memset(msg.msg_text, 0, BUFFER_SIZE);
			if (msgrcv(qid, (void*)&msg, BUFFER_SIZE, 0, 0) < 0)   //��ȡ��Ϣ������˭����
			{
				perror("msgrcv");
				exit(1);
			}
			printf("The message from process %ld : %s", msg.msg_type, msg.msg_text);		
			
		} while(strncmp(msg.msg_text, "Please Register Port RS485-1\r\n", strlen("Please Register Port RS485-1\r\n")));
		
		sleep(5);
		
		
		memset(msg.msg_text, 0, BUFFER_SIZE);
		msg.msg_type=MSG_TYPE_ACK;
		
		memcpy(msg.msg_text,"Register Port RS485-1 Sucessful\r\n",sizeof("Register Port RS485-1 Successful\r\n"));
		if ((msgsnd(qid, &msg, strlen(msg.msg_text), 0)) < 0)
		{
			perror("message posted");
			return -1;
		}


	}

	return 0;
}
 





