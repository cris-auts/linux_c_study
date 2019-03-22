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
	char interface[128];
	printf("1\r\n");
	COMM_InterfaceRegister(interface, 128);
	printf("2\r\n");

	while(1){
	
		sleep(5);
	
	printf("r\r\n");
	}
	return 0;
}
 





