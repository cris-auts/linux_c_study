#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
 
#define SND_BUF_SIZE 1024
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


int main(int argc, char **argv)
{
	int addr_len =-1;
	char snd_buf[SND_BUF_SIZE] = {0};
	struct sockaddr_in6 addr = {0};
	
	char* app_name = argv[0];
    char* dst_ip = argv[1]; 
    int dst_port = atoi(argv[2]);
    char* snd_msg = argv[3]; 
	int msg_cnt=0;

    if(argc != 4)  
	{  
		printf("\r\nUsage: \r\n%s [ip_addr] [port] [msg]\r\n\r\n",app_name);  
        exit(0);
	} 

	memset(snd_buf,0,sizeof(snd_buf));
	strcpy(snd_buf,snd_msg);

	if((socket_fd=socket(AF_INET6,SOCK_DGRAM,IPPROTO_UDP))<0)
	{
		printf("socket created failed!\r\n");
        exit(0);
	}
	printf("Socket created!\r\n");
	addr_len=sizeof(struct sockaddr_in6);
	memset(&addr,0,sizeof(addr));
	addr.sin6_family=AF_INET6;
	addr.sin6_port=htons(dst_port);
	inet_pton(AF_INET6,dst_ip,&addr.sin6_addr);
	while (1)
	{
		if(sendto(socket_fd, snd_buf, strlen(snd_buf), 0, (struct sockaddr*)&addr, addr_len)<0)
		{
			printf("Send msg error!\r\n");
			close(socket_fd);
			exit(0);
		}
		printf("Send msg success msg_cnt=%d!\r\n",msg_cnt++);
		sleep(1);
	}
	close(socket_fd);
    return 0;
}
