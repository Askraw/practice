#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>

// complie command line
// gcc hello.c -pthread -o hello 
// one more parametre
void thread(void *vargp);

int main(){
    pthread_t tid;
    pthread_create(&tid, NULL, thread, NULL);
    pthread_join(tid, NULL);
    exit(0);
}

void thread(void *vargp){
    printf("hello,world!\n");
    // return NULL;
    return ;
}