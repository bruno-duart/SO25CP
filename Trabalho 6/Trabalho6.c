/*
 ****************************************************
 *         Sistemas Operacionais - 2020/1           *
 *             Trabalho 6 - Jantar dos              *
 *                     Gauleses                     *
 *              Bruno Duarte  1917323               *
 *          brunoduarte@alunos.utfpr.edu.br         *
 ****************************************************
*/

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_NUM_JAVALIS 19
#define NUM_GAULESES 5

int numJavalis = MAX_NUM_JAVALIS;
char nome[NUM_GAULESES] = "BRUNO";
sem_t sem_Coz, sem_Retira, sem_Gau, sem_Lib;

void RetiraJavali(long gaules){
    sem_wait(&sem_Gau);
    if(!numJavalis){
        sem_post(&sem_Coz);
        printf("Gaulês %c(%ld) acordou o cozinheiro\n", nome[gaules], gaules);
        sem_wait(&sem_Retira);
    }
    if(numJavalis){
        numJavalis--;
    }
    sem_post(&sem_Lib);
}

void *Gaules(void *threadid){
    long gaules = (long)threadid;
    while(1){
        sem_post(&sem_Gau);
        RetiraJavali(gaules);
        sem_wait(&sem_Lib);
        printf("Gaulês %c(%ld) comendo. Restam %d Javalis\n", nome[gaules], gaules, numJavalis);
        sleep(rand() % 4 + 1);
    }
    pthread_exit(NULL);
}

void *Cozinheiro(){
    while(1){
        sem_wait(&sem_Coz);
        printf("Cozinheiro reabasteceu os javalis e foi nanar\n");
        numJavalis = MAX_NUM_JAVALIS;
        sem_post(&sem_Retira);
    }
    pthread_exit(NULL);
}

void main(){
    srand(time(NULL));
    sem_init(&sem_Coz, 0, 0);
    sem_init(&sem_Retira, 0, 0);
    pthread_t thread[6];
    long i;
    sem_init(&sem_Gau, 0, 1);
    sem_init(&sem_Lib, 0, 0);
    
    
    for(i = 0; i < 5; i++)
        pthread_create(&thread[i], NULL, Gaules, (void*)i);
    
    pthread_create(&thread[5], NULL, Cozinheiro, NULL);
    
    for(i = 0; i < 6; i++)
        pthread_join(thread[i], NULL);

    pthread_exit(NULL);
}