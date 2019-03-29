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
#include "msg.h"
#include "dbase.h"





int main(int argc, char** argv)
{   
	UINT32_T rlen=0;
	UINT32_T wlen=0;
	char pipe_wbuf[128]={"APP:1234567890!\r\n"};
	char pipe_rbuf[128];
	INT32_T ch_id=0;
	PRM_MAIN_T usr_cfg;

	
	ch_id=COMM_InterfaceRegister(&usr_cfg,sizeof(usr_cfg),5000);
	printf("$$$$$$$$$$$$$$$$$$ch_id=%d\r\n",ch_id);
	sleep(1);
	if(ch_id<0)
		return 0;
	while(1)
	{
		memset(pipe_rbuf,0,128);
		rlen=COMM_AppReadDat(ch_id,pipe_rbuf,128);
		if(rlen)
			printf("@@@@@@@@@@APP RCV[%d]:%s\r\n",rlen,pipe_rbuf);
		sleep(1);
		
		wlen=COMM_AppWriteDat(ch_id,pipe_wbuf,128);
		if(wlen == 128)
			printf("**********APP SND[%d]:%s\r\n",wlen,pipe_wbuf);
	}

	return 0;
}
 





