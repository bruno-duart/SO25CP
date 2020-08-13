/*
 ****************************************************
 *         Sistemas Operacionais - 2020/1           *
 *             Trabalho 7 - Jantar dos              *
 *                  Gauleses (SHM)                  *
 *              Bruno Duarte  1917323               *
 *          brunoduarte@alunos.utfpr.edu.br         *
 ****************************************************
*/

#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

#define MAX_NUM_JAVALIS 19
#define NUM_GAULESES 5
#define SHM_ID "/shm_open"

typedef struct _shm_t{
    int numJavalis;
    sem_t sem_Coz, sem_Retira, sem_Lib, sem_Gau;
}shm_t;

shm_t *controle;

void ini_controle(){
    sem_init(&controle->sem_Coz, 1, 0);
    sem_init(&controle->sem_Retira, 1, 0);
    sem_init(&controle->sem_Lib, 1, 0);
    sem_init(&controle->sem_Gau, 1, 1);

    controle->numJavalis = MAX_NUM_JAVALIS;
    printf("Cozinheiro encheu o caldeirão com %d javalis e foi nanar\n", controle->numJavalis);
}

void ini_shm(){
    int fd = shm_open(SHM_ID, O_RDWR|O_CREAT, S_IRUSR|S_IWUSR);

    ftruncate(fd, sizeof(shm_t));

    controle = mmap(NULL, sizeof(shm_t), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
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
    ini_shm();
    ini_controle();
    pthread_t cozinheiro;

    pthread_create(&cozinheiro, NULL, Cozinheiro, NULL);
    pthread_join(cozinheiro, NULL);
    pthread_exit(NULL);
}

// gcc Cozinheiro.c -o Cozinheiro -lpthread -lrt 
// ./Cozinheiro