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
#include "msg.h"
#include "dbase.h"





int main(int argc, char** argv)
{   
	UINT32_T rlen=0;
	UINT32_T wlen=0;
	char pipe_wbuf[128]={"APP:1234567890!\r\n"};
	char pipe_rbuf[128];
	INT32_T ch_id=0;
	
	INT32_T ch_id1=0;
	PRM_MAIN_T usr_cfg;
	
	COMM_InterfaceInit();

	
	ch_id=COMM_InterfaceRegister(&usr_cfg,sizeof(usr_cfg),5000);
	printf("$$$$$$$$$$$$$$$$$$ch_id=%d\r\n",ch_id);
	sleep(5);
	
	ch_id1=COMM_InterfaceRegister(&usr_cfg,sizeof(usr_cfg),5000);
	printf("$$$$$$$$$$$$$$$$$$ch_id=%d\r\n",ch_id1);
	if((ch_id<0)||(ch_id1<0))
		return 0;
	
	while(1)
	{
		#if 1
		memset(pipe_rbuf,0,128);
		rlen=COMM_AppReadDat(ch_id,pipe_rbuf,128);
		if(rlen)
			printf("ch_id=%d@@@@@@@@@@APP RCV[%d]:%s\r\n",ch_id,rlen,pipe_rbuf);
		sleep(1);
		
		wlen=COMM_AppWriteDat(ch_id,pipe_wbuf,128);
		if(wlen == 128)
			printf("ch_id=%d**********APP SND[%d]:%s\r\n",ch_id,wlen,pipe_wbuf);

		//#else
		memset(pipe_rbuf,0,128);
		rlen=COMM_AppReadDat(ch_id1,pipe_rbuf,128);
		if(rlen)
			printf("ch_id1=%d@@@@@@@@@@APP RCV[%d]:%s\r\n",ch_id1,rlen,pipe_rbuf);
		sleep(1);
		
		wlen=COMM_AppWriteDat(ch_id1,pipe_wbuf,128);
		if(wlen == 128)
			printf("ch_id1=%d**********APP SND[%d]:%s\r\n",ch_id1,wlen,pipe_wbuf);
		#endif
	}

	return 0;
}
 





