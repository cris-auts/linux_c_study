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
	char interface[1024];
	char pipe_wbuf[128]={"hello,pipe!\r\n"};
	char pipe_rbuf[128];
		while(1)
		{
			//COMM_InterfaceRegister(interface,1024,5000);
			memset(pipe_rbuf,0,128);
			//COMM_InterfaceWriteDat(1,pipe_wbuf,128);
			COMM_InterfaceReadDat(1,pipe_rbuf,128);
			printf("%s\r\n",pipe_rbuf);
			usleep(500);
		}

	return 0;
}
 





