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
#include "rio.h"
// printf fprintf when meet  \n  will refresh buffer
// pritnf  if not \n will not print to stdout

//  用printf()输出时是先输出到缓冲区，然后再从缓冲区送到屏幕上。linux下缓冲区刷新到屏幕这一步一般可以通过一下方式触发：
// 1使用fflush（stdout）强制刷新标准输出缓冲区。
// 2.缓冲区已满。
// 3.scanf()要在缓冲区里取数据时会先将缓冲区刷新。
// 4.\n进入缓冲区时。
// 5. 程序结束时

// 值得注意就是这个sprintf 把const char× 读到buf里 每次操作其实最后面都添加里一个 \0 这也是这块内存能够反复读取的原因
// 其实后面的空间仍然有字符 但是系统会读到 \0 就停止
void func1(){
    char buf[1000];
    char wbuf[1000];
    sprintf(buf, "HTTP/1.0 %s %s\r\n", "FORBIDDEN", "short_msg");
    // rio_writen(STDOUT_FILENO, buf, strlen(buf));
    printf("buf: %s\n sizeof: %d\n", buf, strlen(buf));
    sprintf(buf, "Content-type: text/html\r\n");
    // rio_writen(STDOUT_FILENO, buf, strlen(buf));
    printf("buf: %s\n sizeof: %d\n", buf, strlen(buf));
    for(int i=25; i<28; i++) printf("%d\n", buf[i]);
    // printf("\r helloworld");
}
void func2(){
    printf("1 2 3");
    
    fork();
    fork();
}
void func3(){
    printf("1 2 3\n");
    fork();
    fork();
}
void func4(){
    printf("1 2 3");
    int input;
    scanf("%d", &input);
    printf("output: %d\n", input);
}
void func5(){
    printf("ddddddd\r"); /* \r 是把光标移动到开头而printf要输出需要结束或者遇到换行 */ /* [0,光标所在处)*/
    printf("12345\n");   /*  换句话说 并不是没有printf输出带有反斜线r的内容，而是光标在开头而已所以加上换行符就自然显示出来啦 */
    // printf("ddddddd\r");
}
int main(){
    // func1();
    // printf("\nab\bsi\rha");
    func1();
    return 0;
}