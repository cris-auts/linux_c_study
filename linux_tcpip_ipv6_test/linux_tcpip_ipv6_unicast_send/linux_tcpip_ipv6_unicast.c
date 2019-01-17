#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>



int main(int argc, char **argv)
{
	int mysocket=-1;
	int addr_len =-1;
	char buf[200] = {0};
	struct sockaddr_in6 addr = {0};

	memset(buf,0,sizeof(buf));
	strcpy(buf,"unicast test message!\r\n");

	if((mysocket=socket(AF_INET6,SOCK_DGRAM,IPPROTO_UDP))<0)
	{
		printf("socket created failed!\r\n");
		return;
	}

	addr_len=sizeof(struct sockaddr_in6);
	memset(&addr,0,sizeof(addr));
	addr.sin6_family=AF_INET6;
	addr.sin6_port=htons(7838);
	inet_pton(AF_INET6,"fe80::20c:29ff:fe95:6ffc",&addr.sin6_addr);
	if(sendto(mysocket, buf, strlen(buf), 0, (struct sockaddr*)&addr, addr_len)<0)
	{
		printf("send error!\r\n");
		return;
	}
		
    return 0;
}
