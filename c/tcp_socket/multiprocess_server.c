#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define BUFFERSIZE 1024

int main(int argc, const char *argv[]) {
    int ret, listen_sockfd, conn_sockfd;
    struct sockaddr_in listen_sockaddr, conn_sockaddr;
    socklen_t conn_addr_len;
    char buffer[BUFFERSIZE];
    pid_t pid;
    ssize_t size;
    

    // NOTE Create socket.
    listen_sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(listen_sockfd == -1) {
        printf("[ERROR] Create socket is error!\n");
        return -1;
    }

    // NOTE Set socket address.
    bzero(&listen_sockaddr, sizeof(listen_sockaddr));
    listen_sockaddr.sin_family = AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &listen_sockaddr.sin_addr);
    listen_sockaddr.sin_port = htons(9000);

    // NOTE Bind socket to socket address.
    ret = bind(listen_sockfd, (struct sockaddr *)&listen_sockaddr, sizeof(listen_sockaddr));
    if(ret == -1) {
        printf("[ERROR] Bind socket to socket address is failed.\n");
        return -1;
    }
    // NOTE listen socket.
    ret = listen(listen_sockfd, 5);
    if(ret == -1) {
        printf("[ERROR] Listening socket address is faild.\n");
        return -1;
    }

    printf("[DEBUG]: This progress is %d, and listen %s:%d ...\n",
           getpid(),
           inet_ntoa(listen_sockaddr.sin_addr),
           ntohs(listen_sockaddr.sin_port));

    // NOTE Reply the client connection.
    while(1) {
        bzero(&conn_sockaddr, sizeof(conn_sockaddr));
        conn_addr_len = sizeof(conn_sockaddr);

        // NOTE Accept the client connection.
        conn_sockfd = accept(listen_sockfd, (struct sockaddr *)&conn_sockaddr, &conn_addr_len);
        // if(conn_sockfd == -1) {
        //     printf("[ERROR] Accpet is error!\n");
        //     continue;
        // }

        // NOTE fork for client connection.
        pid = fork();
        
        // NOTE Child process.
        if(pid == 0) {
            close(listen_sockfd);    
            bzero(buffer, BUFFERSIZE);
            printf("[INFO] fork %d, Accept a client connection: %s:%d\n",
                   getpid(),
                   inet_ntoa(conn_sockaddr.sin_addr),
                   ntohs(conn_sockaddr.sin_port)
            );

            // NOTE Read.
            while(1) {
                size = read(conn_sockfd, buffer, sizeof(buffer));
                if(size == -1) {
                    printf("[INFO] Client was lost!\n");
                    snprintf(buffer, sizeof(buffer),"quit");
                    write(conn_sockfd, buffer, sizeof(buffer));
                    close(conn_sockfd);
                    exit(0);
                }

                printf("from %s:%d message: %s\n",
                    inet_ntoa(conn_sockaddr.sin_addr),
                    ntohs(conn_sockaddr.sin_port),
                    buffer);

                write(conn_sockfd, buffer, sizeof(buffer));
            }
        }
        // NOTE Host process. 
        else {
            close(conn_sockfd);
        }
        
    }

    return 0;
}
