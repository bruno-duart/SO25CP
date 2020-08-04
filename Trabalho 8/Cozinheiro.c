#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/stat.h>

#define MAX_NUM_JAVALIS 19
#define NUM_GAULESES 5

typedef struct _pipe_t{
    int numJavalis;
    sem_t sem_Coz, sem_Retira, sem_Lib, sem_Gau;
}pipe_t;

pipe_t *controle;

void ini_controle(){
    sem_init(&controle->sem_Coz, 1, 0);
    sem_init(&controle->sem_Retira, 1, 0);
    sem_init(&controle->sem_Lib, 1, 0);
    sem_init(&controle->sem_Gau, 1, 1);

    controle->numJavalis = MAX_NUM_JAVALIS;
    printf("Cozinheiro encheu o caldeirão com %d javalis e foi nanar\n", controle->numJavalis);
}

void *Cozinheiro(){
    while(1){
        sem_wait(&controle->sem_Coz);
        controle->numJavalis = MAX_NUM_JAVALIS;
        printf("Cozinheiro encheu o caldeirão com %d javalis e foi nanar.\n", controle->numJavalis);
        sem_post(&controle->sem_Retira);
    }
    pthread_exit(NULL);
}

int main(){
    ini_controle();
    pthread_t cozinheiro;

    pthread_create(&cozinheiro, NULL, Cozinheiro, NULL);
    pthread_join(cozinheiro, NULL);
    pthread_exit(NULL);
}

// gcc Cozinheiro.c -o Cozinheiro -lpthread -lrt 
// ./Cozinheiro