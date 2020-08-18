/*
 ****************************************************
 *         Sistemas Operacionais - 2020/1           *
 *             Trabalho 8 - Jantar dos              *
 *                 Gauleses (PIPES)                 *
 *              Bruno Duarte  1917323               *
 *          brunoduarte@alunos.utfpr.edu.br         *
 ****************************************************
*/
//Código fonte referente aos gauleses

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
#define ever ;;

typedef struct _pipe1_t{
    int numJavalis;
}pipe1_t;

typedef struct _pipe2_t{
    char controle;
}pipe2_t;

pipe1_t jav;
pipe2_t pedido;
int fd[2];
sem_t sem_Retira, sem_Gau, sem_Mesa;
char nome[5] = "BRUNO";

void ini_controle(){
    sem_init(&sem_Retira, 0, 0);
    sem_init(&sem_Gau, 0, 0);
    sem_init(&sem_Mesa, 0, 1);
}

void RetiraJavali(long gaules){
    sem_wait(&sem_Retira);
    read(fd[1], &jav, sizeof(pipe1_t)); //Lê que encheu
    if(jav.numJavalis == 0){
        printf("Gaulês %c(%ld) acordou o cozinheiro\n", nome[gaules], gaules);
        pedido.controle = 'E';
        write(fd[0], &pedido, sizeof(pipe2_t)); //Solicita encher
        read(fd[1], &jav, sizeof(pipe1_t)); //Lê que encheu
    }
    if(jav.numJavalis > 0){
        pedido.controle = 'B';
        write(fd[0], &pedido, sizeof(pipe2_t)); //Solicita retirar
    }
    sem_post(&sem_Gau);
}

void *Gaules(void *threadid){
    long gaules = (long)threadid;
    while(1){
        sem_wait(&sem_Mesa);
        sem_post(&sem_Retira);
        RetiraJavali(gaules);
        sem_wait(&sem_Gau);
        printf("Gaulês %c(%ld) comendo. Restam %d Javalis\n", nome[gaules], gaules, jav.numJavalis - 1);
        sem_post(&sem_Mesa);
        sleep(rand() % 3 + 1);
    }
    pthread_exit(NULL);
}

int main(){
    srand(time(NULL));
    mkfifo("retirar", 0666);
    mkfifo("servir", 0666);
    
    ini_controle();
    fd[0] = open("retirar", O_WRONLY);
    fd[1] = open("servir", O_RDONLY);

    pthread_t gauleses[NUM_GAULESES];
    //read(fd[1], &jav, sizeof(pipe1_t)); //Lê que encheu
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
// /mnt/c/Users/bruno/OneDrive/'Área de Trabalho'/UTFPR/'7º Período'/SO25CP/Trabalhos/SO25CP/'Trabalho 8'
// /media/brunoduarte/Acer/Users/bruno/OneDrive/'Área de Trabalho'/UTFPR/'7º Período'/SO25CP/Trabalhos/SO25CP/'Trabalho 8'
