/*
 ****************************************************
 *         Sistemas Operacionais - 2020/1           *
 *             Trabalho 8 - Jantar dos              *
 *                 Gauleses (PIPES)                 *
 *              Bruno Duarte  1917323               *
 *          brunoduarte@alunos.utfpr.edu.br         *
 ****************************************************
*/
//Código fonte referente ao cozinheiro

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <mqueue.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MAX_NUM_JAVALIS 19
#define NUM_GAULESES 5

typedef struct _msgbuff_t{
    int controle;
}msgbuff_t;

msgbuff_t a, r;
msgbuff_t *acorda = &a, *retira = &r;
mqd_t fd;

int main(){
    struct mq_attr attr;

    attr.mq_maxmsg = MAX_NUM_JAVALIS + 1;
	attr.mq_msgsize = sizeof(msgbuff_t);
	attr.mq_flags = 0;
    
	mq_unlink("/myqueue");
	fd = mq_open("/myqueue", O_RDWR|O_CREAT, 0666, &attr);

    printf("Cozinheiro encheu o caldeirão com %d javalis e foi nanar\n", MAX_NUM_JAVALIS);
    retira->controle = 1;
    printf("RETIRA %d\n", retira->controle);
    for(int i = 0; i < MAX_NUM_JAVALIS; i++)
        mq_send(fd, (void*)retira, sizeof(msgbuff_t), 0);
    retira->controle = 0;
    mq_send(fd, (void*)retira, sizeof(msgbuff_t), 0);

    while(1){
        mq_receive(fd, (void*)acorda, sizeof(msgbuff_t), 0);
        if(acorda->controle == 1){
            printf("Cozinheiro encheu o caldeirão com %d javalis e foi nanar.\n", MAX_NUM_JAVALIS);
            retira->controle = 1;
            for(int i = 0; i < MAX_NUM_JAVALIS; i++)
                mq_send(fd, (void*)retira, sizeof(msgbuff_t), 0);
            retira->controle = 0;
            mq_send(fd, (void*)retira, sizeof(msgbuff_t), 0);
        }
        //write(fd[1], &jav, sizeof(pipe1_t));
    }
}
// gcc Cozinheiro.c -o Cozinheiro -lpthread -lrt 
// ./Cozinheiro
// /mnt/c/Users/bruno/OneDrive/'Área de Trabalho'/UTFPR/'7º Período'/SO25CP/Trabalhos/SO25CP/'Trabalho 9'  
// /media/brunoduarte/Acer/Users/bruno/OneDrive/'Área de Trabalho'/UTFPR/'7º Período'/SO25CP/Trabalhos/SO25CP/'Trabalho 9'