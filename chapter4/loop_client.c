#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define BUFSIZE 1024
void error_handling(char *message);

int main(int argc, char *argv[]) {
    if(argc != 3) {
        printf("Usage : %s <ip> <port> \n", argv[0]);
        exit(1);
    }
    struct sockaddr_in serv_addr;
    char c;
    int strlen;
    char message[BUFSIZ];

    int sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock == -1) {
        error_handling("socket() error");
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
        error_handling("connect() error");
    }

    while(1) {
        printf("Input message(Q to quit): ");
        while((c = getchar()) != 'Q' && c != '\n') {
            write(sock, &c, sizeof(c));
        }

        if (c == 'Q') {
            break;
        }

        strlen = read(sock, message, BUFSIZE - 1);
        message[strlen] = 0;
        printf("Message from server: %s\n", message);
    }

    close(sock);
    exit(0);
}

void error_handling(char *message) {
    fputs(message, stdout);
    fputc('\n', stdout);
    exit(1);
}