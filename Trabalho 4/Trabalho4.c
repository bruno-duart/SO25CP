#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>

#define NUM_THREADS 5

sem_t thr[NUM_THREADS];

void *semA(void *threadId){
    printf("Iniciando A\n");
    sleep(rand() % 4 + 1);
    sem_post(&thr[0]);
    printf("Encerrando A\n");
    pthread_exit(NULL);  
}
void *semB(void *threadId){
    printf("Iniciando B\n");
    sem_post(&thr[1]);
    sleep(rand() % 4 + 1);
    printf("Encerrando B\n");
    pthread_exit(NULL);  
}
void *semC(void *threadId){
    sem_wait(&thr[0]);
    sem_wait(&thr[1]);
    printf("Iniciando C\n");
    sleep(rand() % 4 + 1);
    sem_post(&thr[2]);
    sem_post(&thr[3]);
    printf("Encerrando C\n");
    pthread_exit(NULL);    
}
void *semD(void *threadId){
    sem_wait(&thr[2]);
    printf("Iniciando D\n");
    sleep(rand() % 4 + 1);
    printf("Encerrando D\n");
    pthread_exit(NULL);  
}
void *semE(void *threadId){
    sem_wait(&thr[3]);
    printf("Iniciando E\n");
    sleep(rand() % 4 + 1);
    printf("Encerrando E\n");
    pthread_exit(NULL);  
}
int main(){
    pthread_t threads[NUM_THREADS];
    srand(time(NULL));
    
    for(int i = 2; i < NUM_THREADS; i++)
        sem_init(&thr[i], 0, 0);
    pthread_create(&threads[0], NULL, semA, NULL);
    pthread_create(&threads[1], NULL, semB, NULL);
    pthread_create(&threads[2], NULL, semC, NULL);
    pthread_create(&threads[3], NULL, semD, NULL);
    pthread_create(&threads[4], NULL, semE, NULL);

    pthread_exit(NULL);  
}