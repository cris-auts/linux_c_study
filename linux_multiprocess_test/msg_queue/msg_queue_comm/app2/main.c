#include "std_globals.h"





 
INT_T main(INT_T argc, CHAR_T *argv[])
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
		sleep(10);
		printf ("\r\nRCV....................................................................\r\n");
		memset(&msg.msg_text, 0, sizeof(MSG_TEXT_T));
		msg.msg_type = MSG_TYPE_REG_CH_REQ;
		
		err = msgrcv(qid, (void*)&msg, sizeof(MSG_TEXT_T), msg.msg_type, IPC_NOWAIT) ;
		if (err < 0)
		{
			printf ("ERRERRERR:msgrcv error,err=%d\r\n",err);
			perror("msgrcv");
			
			sleep(1);
			//exit(1);
			
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
			
			printf("reOpen queue@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ %d\n",qid);
			printf("sizeof(MSG_TEXT_T)=%ld\r\n",sizeof(MSG_TEXT_T));
		}
		else
		{
			printf ("OKOKOK:msg rcv success,msg_type=%ld,text_type=%d\r\n",msg.msg_type,msg.msg_text.reg_ch_if_text.text_type);
			printf ("tips=%s\r\n",msg.msg_text.reg_ch_if_text.tips);

			
			#if 1
			printf ("\r\nSND-------------------------------------------------------------------\r\n");

			if(msg.msg_text.reg_ch_if_text.text_type == TEXT_TYPE_REG_CH_IF)
			{
				memset(&msg.msg_text, 0, sizeof(MSG_TEXT_T));
				msg.msg_type = MSG_TYPE_REG_CH_RSP;
				msg.msg_text.rsp_ch_id_text.text_type = TEXT_TYPE_RSP_CH_ID;
				msg.msg_text.rsp_ch_id_text.ch_id = 9;
				sprintf(msg.msg_text.rsp_ch_id_text.tips,"REG OK!!REG ID=%d\r\n",msg.msg_text.rsp_ch_id_text.ch_id);
				err = msgsnd(qid, &msg, sizeof(MSG_TEXT_T), IPC_NOWAIT);
				if(err < 0)
				{
					printf ("ERRERRERR:msgsnd error,err=%d\r\n",err);
					perror("message posted");
				}
				else
				{
					printf ("YYYYYYYYY:REG OK,msg_type=%ld,text_type=%d\r\n",msg.msg_type,msg.msg_text.rsp_ch_id_text.text_type);
					printf ("tips=%s\r\n",msg.msg_text.rsp_ch_id_text.tips);
				}
			}
			else
			{
				memset(&msg.msg_text, 0, sizeof(MSG_TEXT_T));
				msg.msg_type = MSG_TYPE_REG_CH_RSP;
				msg.msg_text.rsp_ch_id_text.text_type = TEXT_TYPE_RSP_CH_ID;
				msg.msg_text.rsp_ch_id_text.ch_id = 0xff;
				sprintf(msg.msg_text.rsp_ch_id_text.tips,"REG ID=%d\r\n",msg.msg_text.rsp_ch_id_text.ch_id);
				
				err = msgsnd(qid, &msg, sizeof(msg.msg_text), IPC_NOWAIT);
				if(err < 0)
				{
					printf ("ERRERRERR:msgsnd error,err=%d\r\n",err);
					perror("message posted");
				}
				else
				{
					printf ("XXXXXXXXXXX:REG ERR,msg_type=%ld,text_type=%d\r\n",msg.msg_type,msg.msg_text.rsp_ch_id_text.text_type);
					printf ("tips=%s\r\n",msg.msg_text.rsp_ch_id_text.tips);
				}
			}
			#endif 
		}
		//sleep(1);
	 
	}
	exit(0);
}
