#include <stdio.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

#define RCV_BUF_SIZE 1024
int socket_fd = 0;


void signal_exit_handler( int signal)
{
    if(signal == SIGINT)
    {
        printf("Ctrl+C has been pressed down! App exiting!\r\n");
		if(socket_fd > 0)
			close(socket_fd);
        exit(0);
    }
}


int main(int argc,char **argv)
{

    int ret = 0;
    char rcv_buf[RCV_BUF_SIZE];
    struct sockaddr_in6 address,addr;
    socklen_t len = sizeof(addr);
	
	char* app_name=argv[0];
    char* listen_ip = argv[1]; 
    int listen_port = atoi(argv[2]);


    if(argc != 3)  
	{  
		printf("\r\nUsage: \r\n%s [ip_addr] [port] \r\n\r\n",app_name);  
        exit(0);
	}  


    bzero(&address,sizeof(address));
    address.sin6_family = AF_INET6;
    inet_pton(AF_INET6,listen_ip,&address.sin6_addr);
    address.sin6_port = htons(listen_port);
	
    socket_fd = socket(PF_INET6,SOCK_DGRAM,IPPROTO_UDP);
	if(socket_fd < 0)
	{
		printf("Socket created failed! err=%d\r\n",socket_fd);
        exit(0);
	}
	printf("Socket created!\r\n");
    ret = bind(socket_fd,(struct sockaddr *)&address,sizeof(address));
	if(ret == -1)
	{
		printf("Socket bind failed! err=%d\r\n",ret);
		close(socket_fd);
        exit(0);
	}

	signal(SIGINT, signal_exit_handler);
	while(1)
	{
	    printf("Ready to recevie data!\r\n");
	    ret = recvfrom(socket_fd,rcv_buf,RCV_BUF_SIZE-1,0,(struct sockaddr *)&addr,&len);
	    rcv_buf[ret] = '\0';
	    printf("recevice new data:\r\n%s\r\n",rcv_buf);
	}
    return 0;
}

