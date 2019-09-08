#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<errno.h>
void *thread(void *vargp);
void P(sem_t *sem);
void V(sem_t *sem);
void unix_error(char *msg);

volatile int cnt = 0;
sem_t mutex;

int main(int argc, char **argv){
    int nithers;
    pthread_t tid1, tid2;

    if(argc != 2){
        printf("error input");
        exit(0);
    }
    nithers = atoi(argv[1]);

    sem_init(&mutex, 0 ,1);
    pthread_create(&tid1, NULL, thread, &nithers);
    pthread_create(&tid2, NULL, thread, &nithers);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    if(cnt != (2*nithers)){
        printf("BOOM ! cnt=[%d]\n", cnt);
    }else
    {
        printf("OK ! cnt=[%d]\n", cnt);
    }
    exit(0);
}

void P(sem_t *sem) 
{
    if (sem_wait(sem) < 0)
	unix_error("P error");
}

void V(sem_t *sem) 
{
    if (sem_post(sem) < 0)
	unix_error("V error");
}

void unix_error(char *msg) /* Unix-style error */
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}

void *thread(void *vargp){
    int i;
    int niters = *((int *)vargp);
    for(i=0; i<niters; i++){
        P(&mutex);
        cnt++;
        V(&mutex);
    }
    return NULL;
}