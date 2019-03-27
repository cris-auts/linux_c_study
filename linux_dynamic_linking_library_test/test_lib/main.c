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





int main(int argc, char** argv)
{   
	UINT32_T rlen=0;
	UINT32_T wlen=0;
	char pipe_wbuf[128]={"APP:1234567890!\r\n"};
	char pipe_rbuf[128];
	char interface[1024];
	
	COMM_InterfaceRegister(interface,1024,5000);
	sleep(10);
	while(1)
	{
		memset(pipe_rbuf,0,128);
		rlen=COMM_AppReadDat(1,pipe_rbuf,128);
		if(rlen)
			printf("@@@@@@@@@@APP RCV[%d]:%s\r\n",rlen,pipe_rbuf);
		usleep(500);
		
		wlen=COMM_AppWriteDat(1,pipe_wbuf,128);
		if(wlen == 128)
			printf("**********APP SND[%d]:%s\r\n",wlen,pipe_wbuf);
	}

	return 0;
}
 





