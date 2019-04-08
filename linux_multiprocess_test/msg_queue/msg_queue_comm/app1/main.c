#include "std_globals.h"





 
int main(INT_T argc, CHAR_T *argv[])
{
	INT_T qid;
	key_t key;
	MSG_T msg;
 
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
	   printf("Enter some message to the queue(enter 'quit' to exit):");
	    if ((fgets(msg.msg_text, BUFFER_SIZE, stdin)) == NULL)
	    {
	        puts("no message");
	        exit(1);
	    }
	 
		msg.msg_type = getpid();
		if ((msgsnd(qid, &msg, strlen(msg.msg_text), 0)) < 0)
		{
			perror("message posted");
			exit(1);
		}
	 
		if (strncmp(msg.msg_text, "quit", 4) == 0)
		{
			break;
		}
	}
	exit(0);
}
