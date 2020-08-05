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

typedef struct _pipe1_t{
    int numJavalis;
}pipe1_t;

typedef struct _pipe2_t{
    char comando;
}pipe2_t;

pipe1_t *jav;

sem_t sem_Retira, sem_Gau;

char nome[5] = "BRUNO";

void ini_controle(){
    sem_init(&sem_Retira, 0, 0);
    sem_init(&sem_Gau, 0, 0);
}


void RetiraJavali(long gaules){
    sem_wait(&sem_Retira);
    if(!jav->numJavalis){
        printf("Gaulês %c(%ld) acordou o cozinheiro\n", nome[gaules], gaules);
        cont->comando = 'E';
        //write(); //Solicita encher
        //read(); //Lê que encheu
    }
    if(jav->numJavalis){
        cont->comando = 'B';
        //write(); //Solicita retirar
        //read(); //Recebe um javali
    }
    sem_post(&sem_Gau);
}

void *Gaules(void *threadid){
    long gaules = (long)threadid;
    while(1){
        sem_post(&sem_Retira);
        RetiraJavali(gaules);
        sem_wait(&sem_Gau);
        printf("Gaulês %c(%ld) comendo. Restam %d Javalis\n", nome[gaules], gaules, jav->numJavalis);
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