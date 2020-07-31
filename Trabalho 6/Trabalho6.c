#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

#define MAX_NUM_JAVALIS 19
#define NUM_GAULESES 5
#define numBreak 15

int j=0, numJavalis = MAX_NUM_JAVALIS;
char nome[NUM_GAULESES] = "BRUNO";
sem_t sem_Coz, sem_Gau;
/*
void Gaules(){
    while(1){
        j = RetiraJavali();
        ComeJavali(j);
    }
}*/

void *Comer(void *trheadid){
    long tid = (long)tid;
    printf("%ld\n",pthread_self());
    while(1){
        if(numJavalis){
            numJavalis--;
            printf("Gaulês %c(%ld) comendo\n", nome[tid], tid);
        }else{
            printf("Gaulês %c(%ld) acordou o cozinheiro\n", nome[tid], tid);
            sem_post(&sem_Coz);
            sem_wait(&sem_Gau);
        }
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
    sem_init(&sem_Gau, 0, 0);
    pthread_t thread[2];
    long i = 0;
    pthread_create(&thread[0], NULL, Cozinheiro, (void*)i++);
    pthread_create(&thread[1], NULL, Comer, (void*)8);

    pthread_join(thread[0], NULL);
    pthread_join(thread[1], NULL);

    pthread_exit(NULL);
    return 0;
}