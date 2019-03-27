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
	int wlen=0;
	int rlen=0;
	char interface[1024];
	char pipe_wbuf[128]={"abcdefghij\r\n"};
	char pipe_rbuf[128];
		while(1)
		{
			//COMM_InterfaceRegister(interface,1024,5000);
			memset(pipe_rbuf,0,128);
			#if 1
			wlen=COMM_InterfaceWriteDat(1,pipe_wbuf,128);
			if((wlen>0)&&(wlen==128))
				printf("write ok\r\n");
			#else
			wlen=COMM_InterfaceReadDat(1,pipe_rbuf,128);
			if(wlen>0)
				printf("%s",pipe_rbuf);
			#endif
			usleep(500);
		}

	return 0;
}
 





