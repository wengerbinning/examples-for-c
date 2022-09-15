#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFFERSIZE 1024

int main(int argc, const char * argv[]) {
    int ret, listen_sockfd, conn_sockfd;
    struct sockaddr_in listen_sockaddr, conn_sockaddr;
    socklen_t conn_addr_len;
    char buffer[BUFFERSIZE];
    ssize_t size;

    // NOTE Create listen socket.
    listen_sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if( listen_sockfd < 0 ) {
        printf("[ERROR]: Create listening socket was failed!\n");
        return -1;
    }

    // NOTE Set listen socket address.
    bzero(&listen_sockaddr, sizeof(listen_sockaddr));
    listen_sockaddr.sin_family = AF_INET;
    listen_sockaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    listen_sockaddr.sin_port = htons(9000);

    // NOTE Bind listen socket to socket address.
    ret = bind(listen_sockfd, (struct sockaddr*)&listen_sockaddr, (socklen_t)sizeof(listen_sockaddr));
    if(ret < 0) {
        printf("[ERROR]: Bound socket to sockaddr was failed!\n");
        return -1;
    }

    // NOTE listen socket address.
    ret = listen(listen_sockfd, 5);
    if(ret < 0) {
        printf("[ERROR]: Listen sockaddr was failed!\n");
        return -1;
    }

    printf("[DEBUG]: This progress is %d, and listen %s:%d ...\n",
           getpid(),
           inet_ntoa(listen_sockaddr.sin_addr),
           ntohs(listen_sockaddr.sin_port));

    // TODO deal when client connection.
    while(1) {
        int ext = 1;
        memset(&conn_sockaddr, 0, sizeof(conn_sockaddr));
        conn_addr_len = sizeof(conn_sockaddr);

        // NOTE accept a connection socket.
        conn_sockfd = accept(listen_sockfd, (struct sockaddr *)&conn_sockaddr, &conn_addr_len);
        if(conn_sockfd < 0) {
            printf("[ERROR]: Accept client connection socket was failed!\n");
            continue;
        }

        printf("[INFO] Accept a client connection: %s:%d\n",
               inet_ntoa(conn_sockaddr.sin_addr),
               ntohs(conn_sockaddr.sin_port)
               );

        while(1) {
            bzero(buffer, sizeof(buffer));
            size = read(conn_sockfd, buffer, sizeof(buffer));
            if (size < 0) {
                printf("[INFO] Client connection is lost!\n");
                close(conn_sockfd);
                break;
            }

            printf("from %s:%d >> %s\n",
                   inet_ntoa(conn_sockaddr.sin_addr),
                   ntohs(conn_sockaddr.sin_port),
                   buffer
            );
            if(0 == strncmp(buffer,"server quit",sizeof("server quit")-1)) {
                ext = 0;
            }

            write(conn_sockfd, buffer, sizeof(buffer));
        }

        // NOTE Check server need or not exit.
        if( ext != 1 ) {
            break;
        }
    }

    printf("[DEBUG] Server exit.\n");
    return 0;
}
