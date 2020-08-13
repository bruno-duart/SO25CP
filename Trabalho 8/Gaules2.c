// gcc Gaules2.c -o Gaules2 -lpthread -lrt 
// ./Gaules2
// /mnt/c/Users/bruno/OneDrive/'Área de Trabalho'/UTFPR/'7º Período'/SO25CP/Trabalhos/SO25CP/'Trabalho 8'
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

typedef struct _pipe2_t{
    char controle;
}pipe_t;

sem_t sem_Retira, sem_Gau;
pipe_t *gau, *coz;
int numJavalis = MAX_NUM_JAVALIS, fd[2];
char nome[5] = "BRUNO";

void ini_controle(){
    sem_init(&sem_Retira, 0, 0);
    sem_init(&sem_Gau, 0, 0);
}

void RetiraJavali(long gaules){
    sem_wait(&sem_Retira);
    read(fd[1], coz, sizeof(pipe_t));
    if(coz->controle == 'V'){
        printf("Gaulês %c(%ld) acordou o cozinheiro\n", nome[gaules], gaules);
        write(fd[0], gau, sizeof(pipe_t));
        read(fd[1], coz, sizeof(pipe_t));
        numJavalis = MAX_NUM_JAVALIS;
        printf("Entrei\n");
    }
    if(coz->controle == 'J'){
        numJavalis--; 
    }
    sem_post(&sem_Gau);
}

void *Gaules(void *threadid){
    long gaules = (long)threadid;
    while(1){     
        sem_post(&sem_Retira);   
        RetiraJavali(gaules);
        sem_wait(&sem_Gau);
        printf("Gaulês %c(%ld) comendo. Restam %d Javalis\n", nome[gaules], gaules, numJavalis);
        sleep(rand() % 3 + 1);
    }
    pthread_exit(NULL);
}

int main(){
    pipe_t gauLocal, cozLocal;
    gau = &gauLocal;
    coz = &cozLocal;
    ini_controle();
    mkfifo("retirar", O_CREAT|O_EXCL);
    mkfifo("servir", O_CREAT|O_EXCL);
    fd[0] = open("retirar", O_WRONLY);
    fd[1] = open("servir", O_RDONLY);
    pthread_t gauleses[NUM_GAULESES];
    gau->controle = 'E';

    for(long i = 0; i < NUM_GAULESES; i++){
        pthread_create(&gauleses[i], NULL, Gaules, (void*)i);
    }
    for(long i = 0; i < NUM_GAULESES; i++){
        pthread_join(gauleses[i], NULL);
    }
    pthread_exit(NULL);
}