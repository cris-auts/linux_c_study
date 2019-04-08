#include "std_globals.h"





 
int main(INT_T argc, CHAR_T *argv[])
{
	INT_T qid;
	key_t key;
	MSG_T msg;
	INT_T err=0;
 
	if ((key = ftok("/tmp", 'a')) == -1)
	{
	    perror("ftok");
	    exit(1);
	}
 
	if ((qid = msgget(key, IPC_CREAT|0666)) == -1)
	{
	    perror("msgget");
	    exit(1);
	}
	
	printf("Open queue %d\n",qid);
 
	while(1)
	{
		memset(&msg.msg_text, 0, sizeof(MSG_TEXT_T));
		msg.msg_type = MSG_TYPE_REG_CH_REQ;
		
		err = msgrcv(qid, (void*)&msg, sizeof(MSG_TEXT_T), msg.msg_type, IPC_NOWAIT) ;
		if (err < 0)
		{
			printf ("ERRERRERR:msgrcv error,err=%d\r\n",err);
			perror("msgrcv");
			
			sleep(1);
			//exit(1);
		}
		else
		{
			printf ("OKOKOK:msg rcv success,msg_type=%ld,text_type=%d\r\n",msg.msg_type,msg.msg_text.reg_ch_if_text.text_type);
			printf ("tips=%s\r\n",msg.msg_text.reg_ch_if_text.tips);
		}
		//sleep(1);
	 
	}
	exit(0);
}
