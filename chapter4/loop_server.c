#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#define BUFSIZE 1024

void error_handling(char *message);

int main(int argc, char *argv[]) {
    if(argc != 2) {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    int serv_sock, clnt_sock;
    struct sockaddr_in serv_addr, clnt_addr;   //头文件<arpa/inet.h>
    int clnt_addrlen = sizeof(clnt_addr);
    char message[BUFSIZE];
    int strlen;

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock == -1) {
        error_handling("socket() error");
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if(bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
        error_handling("bind() error");
    }

    if(listen(serv_sock, 10) == -1) {
        error_handling("listen() error");
    }

    while(clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addrlen)) {
        printf("%d start\n", clnt_sock);
        while(strlen = read(clnt_sock, message, sizeof(message))) {
            write(clnt_sock, message, strlen);
        }

        close(clnt_sock);
        printf("%d over\n", clnt_sock);
    }

    close(serv_sock);

    exit(0);
}

void error_handling(char *message) {
    fputs(message, stdout);
    fputc('\n', stdout);
    exit(1);
}