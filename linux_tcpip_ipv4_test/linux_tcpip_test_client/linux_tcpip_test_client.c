#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(int argc, char *argv[])
{
    int clnt_sock;
    struct sockaddr_in serv_addr;
    int str_len;

    if (argc != 3) {
        printf("Usage: %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    clnt_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (clnt_sock < 0) {
        printf("sock() error\n");
        exit(1);
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if (connect(clnt_sock,
            (struct sockaddr*)&serv_addr,
            sizeof(serv_addr)) == -1) {
        printf("connect() error\n");
        exit(1);
    }

    char buf[1024];

    while (1) {
        memset(buf, 0, sizeof(buf));
        printf("client enter: ");
        fflush(stdout);
        ssize_t size = read(0, buf, sizeof(buf) - 1);
        if (size < 0) {
            printf("read() error\n");
            break;
        } else {
            buf[size - 1] = '\0';
        }
        write(clnt_sock, buf, strlen(buf));
    }
    close(clnt_sock);
    return 0;
}
