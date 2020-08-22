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
#include <mqueue.h>

#define MAX_NUM_JAVALIS 19
#define NUM_GAULESES 5

typedef struct _msgbuff_t{
    int controle;
}msgbuff_t;

msgbuff_t a, r;
msgbuff_t *acorda = &a, *retira = &r;
mqd_t fd1, fd2;
int numJavalis;
sem_t sem_Retira, sem_Gau, sem_Mesa;
char nome[5] = "BRUNO";

void ini_controle(){ //Inicialização dos semáforos
    sem_init(&sem_Retira, 0, 0);
    sem_init(&sem_Gau, 0, 0);
    sem_init(&sem_Mesa, 0, 1);
}

void RetiraJavali(long gaules){
    sem_wait(&sem_Retira);
    if(retira->controle == 0){ //Se o controle for 0, significa que todos os javalis foram consumidos
        printf("Gaulês %c(%ld) acordou o cozinheiro\n", nome[gaules], gaules);
         //Envia um sinal de controle
        mq_send(fd1, (void*)acorda, sizeof(msgbuff_t), 0); //Solicita encher
        printf("Mandei um recadinho\n");
		mq_receive(fd2, (void*)retira, sizeof(msgbuff_t), 0); //Lê que encheu e permite a retirada de um javali
    }
    if(retira->controle){
        retira->controle--; //Retira um javali
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
        printf("Gaulês %c(%ld) comendo. Restam %d Javalis\n", nome[gaules], gaules, retira->controle);
        sem_post(&sem_Mesa);
        sleep(rand() % 3 + 1);
    }
    pthread_exit(NULL);
}

int main(){
    srand(time(NULL));
    struct mq_attr attr;
    attr.mq_maxmsg = 1;
	attr.mq_msgsize = sizeof(msgbuff_t);
	attr.mq_flags = 0;
    
	mq_unlink("/acorda");
	fd1 = mq_open("/acorda", O_RDWR|O_CREAT, 0666, &attr);
	fd2 = mq_open("/retira", O_RDWR);

    ini_controle();
    numJavalis = MAX_NUM_JAVALIS;
    pthread_t gauleses[NUM_GAULESES];acorda->controle = 1;
    printf("antes\n");
    mq_receive(fd2, (void*)retira, sizeof(msgbuff_t), 0); //Lê do buffer
    printf("depois\n");
    for(long i = 0; i < NUM_GAULESES; i++)
        pthread_create(&gauleses[i], NULL, Gaules, (void*)i);

    for(long i = 0; i < NUM_GAULESES; i++)
        pthread_join(gauleses[i], NULL);
    
    pthread_exit(NULL);
}
// gcc Gaules2.c -o Gaules -lpthread -lrt 
// ./Gaules
// /mnt/c/Users/bruno/OneDrive/'Área de Trabalho'/UTFPR/'7º Período'/SO25CP/Trabalhos/SO25CP/'Trabalho 8'
// /media/brunoduarte/Acer/Users/bruno/OneDrive/'Área de Trabalho'/UTFPR/'7º Período'/SO25CP/Trabalhos/SO25CP/'Trabalho 8'
