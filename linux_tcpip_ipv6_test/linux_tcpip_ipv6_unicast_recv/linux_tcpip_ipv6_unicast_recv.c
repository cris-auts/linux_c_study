#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<assert.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>

#define BUFFER_SIZE 1024

int main(int argc,char **argv)
{
    char *ip = argv[1];             //用户自身的IP
    int port = atoi(argv[2]);           //和服务器端口对应及2000
    int ret = 0;
    int client_fd;
    char buf[BUFFER_SIZE];
    struct sockaddr_in6 address,addr;
    socklen_t len = sizeof(addr);

    if(argc <= 2)
    {
        printf("error\n");
    }

    bzero(&address,sizeof(address));
    address.sin6_family = AF_INET6;
    inet_pton(AF_INET6,ip,&address.sin6_addr);
    address.sin6_port = htons(port);
    client_fd = socket(PF_INET6,SOCK_DGRAM,0);
    assert(client_fd >= 0);


    ret = bind(client_fd,(struct sockaddr *)&address,sizeof(address));
    assert(ret != -1);

    printf("准备接收数据\n");
    ret = recvfrom(client_fd,buf,BUFFER_SIZE-1,0,(struct sockaddr *)&addr,&len);
    buf[ret] = '\0';
    printf("\n%s\n",buf);

    return 0;
}

