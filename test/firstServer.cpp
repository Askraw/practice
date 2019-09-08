#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/sendfile.h>
#include<fcntl.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<assert.h>
#include<unistd.h>
#include<string.h>

const int port = 8888;
int main(int argc, char* argv[]){
    if(argc < 0){
        printf("we need 2 params!\n");
        return 1;
    }
    int sockfd;
    int connfd;
    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = PF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    server_addr.sin_port = htons(port);


    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(sockfd >= 0);
    int ret = bind(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr));
    assert(ret != -1);
    ret = listen(sockfd, 2);
    assert(ret != -1);

    while(1){
        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);
        connfd = accept(sockfd, (struct sockaddr *) &client_addr, &client_addr_len);
        if(connfd < 0){
            printf("errno!\n");
        }else{
            char request[1024];
            recv(connfd, request, 1024, 0);
            request[strlen(request)+1] = '\0';  //complete C-string
            printf("%s\n", request);
            printf("successful!\n");

            char buf[520] = "HTTP/1.1 200 ok\r\nconnection: close\r\n\r\n"; // HTTP response
            int s = send(connfd, buf, strlen(buf), 0);
            int fd = open("open.html", O_RDONLY);
            sendfile(connfd, fd, NULL, 2500);
            close(fd);
            close(connfd);
        }

    }
    return 0;
}