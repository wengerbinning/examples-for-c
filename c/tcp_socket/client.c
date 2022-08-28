#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFFERSIZE 1024

int main(int argc, const char *argv[]) {
    int ret, sockfd;
    struct sockaddr_in server_sockaddr, local_sockaddr;
    socklen_t local_addr_len;
    char buffer[BUFFERSIZE];
    ssize_t size;

    // NOTE Create socket.
    sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sockfd < 0) {
        printf("[ERROR]: Create socket is error!\n");
        return -1;
    }

    // NOTE Set server address.
    memset(&server_sockaddr, 0, sizeof(server_sockaddr));
    server_sockaddr.sin_family = AF_INET;
    server_sockaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_sockaddr.sin_port = htons(9000);

    // NOTE Connect to server.
    ret = connect(sockfd, (struct sockaddr *)&server_sockaddr, sizeof(server_sockaddr));
    if(ret < 0) {
        printf("[ERROR] Connect server is error!\n");
        return -1;
    }

    // NOTE Get local socket address information.
    bzero(&local_sockaddr, sizeof(local_sockaddr));
    local_addr_len = sizeof(local_sockaddr);
    ret = getsockname(sockfd, (struct sockaddr *)&local_sockaddr, &local_addr_len);
    if(ret < 0) {
        printf("[ERROR] Get local socket address is error!\n");
        return -1;
    }

    printf("[DEBUG]: Connect server is successful, this process is %d, ,and local socket address is %s:%d\n",
           getpid(),
           inet_ntoa(local_sockaddr.sin_addr),
           ntohs(local_sockaddr.sin_port));

    // TODO you can do something that tell service.
    while(1) {
        bzero(&buffer, sizeof(buffer));
        scanf("%s", buffer);
        size = write(sockfd, buffer, sizeof(buffer));
        if(size < 0) {
            printf("[ERROR] write was failed!\n");
        }

        bzero(&buffer, sizeof(buffer));
        ret = read(sockfd, buffer, sizeof(buffer));
        if(ret < 0) {
            printf("[ERROR] Read from socket is error!\n");
            break;
        }
        printf("%d bytes from server message: %s\n",ret, buffer);

    }

    // close socket.
    close(sockfd);

    return 0;
}
