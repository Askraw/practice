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
#include<netdb.h>

int main(){
    char buf[100];
    read(STDIN_FILENO, buf, 100);
    fputs(buf, stdout);
    // write(STDOUT_FILENO, buf, 100);
    return 0;
}