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
 	printf("sizeof(MSG_TEXT_T)=%ld\r\n",sizeof(MSG_TEXT_T));

	sleep(3);
	while(1)
	{
	
		#if 1
		printf ("\r\nSND-------------------------------------------------------------------\r\n");
		msg.msg_type = MSG_TYPE_REG_CH_REQ;
		msg.msg_text.reg_ch_if_text.text_type = TEXT_TYPE_REG_CH_IF;
		memcpy(msg.msg_text.reg_ch_if_text.tips,"~~~~~~~~~~~REG CH REQ\r\n",sizeof("~~~~~~~~~~~REG CH REQ\r\n"));
		err = msgsnd(qid, &msg, sizeof(msg.msg_text), IPC_NOWAIT);
		if (err < 0)
		{
			printf ("ERRERRERR:msgsnd error,err=%d\r\n",err);
			perror("message posted");
			sleep(1);
		}
		else
		{
			printf ("OKOKOK:msg snd success,msg_type=%ld,text_type=%d\r\n",msg.msg_type,msg.msg_text.reg_ch_if_text.text_type);
			printf ("tips=%s\r\n",msg.msg_text.reg_ch_if_text.tips);
		}
		//sleep(1);
		#endif

		printf ("\r\nRCV....................................................................\r\n");
		memset(&msg.msg_text, 0, sizeof(MSG_TEXT_T));
		msg.msg_type = MSG_TYPE_REG_CH_RSP;
		err = msgrcv(qid, (void*)&msg, sizeof(MSG_TEXT_T), msg.msg_type, IPC_NOWAIT) ;
		if (err < 0)
		{
			printf ("ERRERRERR:msgrcv error,err=%d\r\n",err);
			perror("msgrcv");
			
			sleep(1);
			//exit(1);
		}else{
			printf ("OKOKOK:msg rcv success,msg_type=%ld,text_type=%d\r\n",msg.msg_type,msg.msg_text.rsp_ch_id_text.text_type);
			printf ("tips=%s\r\n",msg.msg_text.rsp_ch_id_text.tips);
		}
	}
	exit(0);
}
