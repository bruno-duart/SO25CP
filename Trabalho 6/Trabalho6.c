#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

#define MAX_NUM_JAVALIS 19
#define NUM_GAULESES 5
#define numBreak 15

int j=0, numJavalis = MAX_NUM_JAVALIS;
char nome[NUM_GAULESES] = "BRUNO";
sem_t sem_Coz, sem_Retira, sem_Gau[NUM_GAULESES];
/*
void Gaules(){
    while(1){
        j = RetiraJavali();
        ComeJavali(j);
    }
}*/

void RetiraJavali(long gaules){
    sem_wait(&sem_Retira);
    if(numJavalis){
        sem_post(&sem_Gau[gaules]);
        numJavalis--;
    }else{
        printf("Gaulês %c(%ld) acordou o cozinheiro\n", nome[gaules], gaules);
        sem_post(&sem_Coz);
    }
}

void *Gaules1(void *threadid){
    long gaules = (long)threadid;
    while(1){
        sem_post(&sem_Retira);
        RetiraJavali(gaules);
        sem_wait(&sem_Gau[gaules]);
        printf("Gaulês %c(%ld) comendo\n", nome[gaules], gaules);
        if(j == 15)
            break;
    }
    pthread_exit(NULL);
}

void *Cozinheiro(){
    while(1){
        sem_wait(&sem_Coz);
        numJavalis = MAX_NUM_JAVALIS;
        sem_post(&sem_Gau);
        j++;
        if(j == 15)
            break;
    }
    pthread_exit(NULL);
}

int main(){
    sem_init(&sem_Coz, 0, 0);
    sem_init(&sem_Retira, 0, 0);
    pthread_t thread[6];
    long i;
    for(i = 0; i < 5; i++)
        sem_init(&sem_Gau[i], 0, 1);
    
    for(i = 0; i < 5; i++)
        pthread_create(&thread[i], NULL, Gaules1, (void*)i);
    
    pthread_create(&thread[0], NULL, Cozinheiro, (void*)i);
    
    for(i = 0; i < 6; i++)
        pthread_join(thread[i], NULL);

    pthread_exit(NULL);
    return 0;
}