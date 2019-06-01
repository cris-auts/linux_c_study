#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>



int main(int argc, char *argv[])
{
   while(1) 
   {
		printf("Hello,Linux!\r\n");
		sleep(1);   
   }
    return 0;
}
