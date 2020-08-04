#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

#define MAX_NUM_JAVALIS 19
#define NUM_GAULESES 5
#define SHM_ID "/shm_open"

typedef struct _pipe_t{
    int numJavalis;
    sem_t sem_Coz, sem_Retira, sem_Lib, sem_Gau;
}pipe_t;
char nome[5] = "BRUNO";


void RetiraJavali(long gaules){
    sem_wait(&controle->sem_Gau);
    if(!controle->numJavalis){
        sem_post(&controle->sem_Coz);
        printf("Gaulês %c(%ld) acordou o cozinheiro\n", nome[gaules], gaules);
        sem_wait(&controle->sem_Retira);
    }
    if(controle->numJavalis){
        controle->numJavalis--;
    }
    sem_post(&controle->sem_Lib);
}

void *Gaules(void *threadid){
    long gaules = (long)threadid;
    while(1){
        sem_post(&controle->sem_Gau);
        RetiraJavali(gaules);
        sem_wait(&controle->sem_Lib);
        printf("Gaulês %c(%ld) comendo. Restam %d Javalis\n", nome[gaules], gaules, controle->numJavalis);
        sleep(rand() % 4 + 1);
    }
    pthread_exit(NULL);
}

int main(){
    pthread_t gauleses[NUM_GAULESES];
    for(long i = 0; i < NUM_GAULESES; i++){
        pthread_create(&gauleses[i], NULL, Gaules, (void*)i);
    }
    for(long i = 0; i < NUM_GAULESES; i++){
        pthread_join(gauleses[i], NULL);
    }
    pthread_exit(NULL);
}
// gcc Gaules.c -o Gaules -lpthread -lrt 
// ./Gaules