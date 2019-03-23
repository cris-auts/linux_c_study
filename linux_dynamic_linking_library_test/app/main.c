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

	while(1){
		sleep(1);
		COMM_InterfaceRegister(interface, 128);
	}
	return 0;
}
 





