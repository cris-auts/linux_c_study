#include <stdio.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>



char * IP = "127.0.0.1";
short PORT = 8888;
int socket_fd=0;
typedef struct sockaddr SA;
void sig_close(void)
{
	close(socket_fd);
	printf ("this is a sig_close\r\n");
	exit(0);
}

void init (void)
{
	printf("sever starting \r\n");
	socket_fd=socket(AF_INET,SOCK_STREAM,0);//协议栈设置为0，表示自动选择
	if(socket_fd == -1)
	{
		printf("socket create fail!\r\n");
	}
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = inet_addr(IP);
	if(bind(socket_fd,(SA*)&addr,sizeof(addr)) == -1)
	{
		printf("socket bind fail!\r\n");
	}
	if (listen(socket_fd,100) == -1)
	{
		printf("socket listen fail!\r\n"); 
    }
    printf("Server init OK!\r\n");
}

void rcv_proc(int sfd)
{
	int size = 0;	
	char buf[512] ={};
	while (size = read(sfd,buf,sizeof(buf)))
	{
		printf("Client %d say:%s",sfd,buf);
		if (write (sfd,buf,strlen(buf)+1))
		{
			printf("Write fail");
		}
		memset(buf,0,sizeof(buf));
	}
	printf("%d has disconnect!\n",sfd);
}

void service()
{
	printf ("Server has started!\n");
	while(1)
	{
		struct sockaddr_in fromaddr;
		socklen_t len=sizeof(fromaddr);
		printf("\r\n Waiting for clients to connect...\r\n");
		int fd = accept(socket_fd,(SA*)&fromaddr,&len);
		if(fd ==-1)
		{
			printf("Clinet connect failed!\r\n");
			continue;
		}
		else
		{
			printf("Has connect to Client:%d\r\n",fd);
		}
		rcv_proc(fd);
	}
}

 
int main (int argc, char* argv[])
{
	signal(SIGINT,(__sighandler_t)sig_close);
    printf("Press <Ctrl+C> to stop server.\r\n");
	init();	
	service();
    return 0;
}
