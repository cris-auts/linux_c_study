#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>     
#include <termios.h>   
#include <errno.h>     



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
			#if 1
			COMM_InterfaceWriteDat(1,pipe_wbuf,128);
			#else
			COMM_InterfaceReadDat(1,pipe_rbuf,128);
			#endif
			printf("%s",pipe_rbuf);
			sleep(5);
		}

	return 0;
}
 





