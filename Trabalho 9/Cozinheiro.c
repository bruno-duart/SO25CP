/*
 ****************************************************
 *         Sistemas Operacionais - 2020/1           *
 *             Trabalho 12 - Jantar dos             *
 *         Gauleses Passagem de Mensagens           *
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
mqd_t fd1, fd2;

int main(){
    struct mq_attr attr;

    attr.mq_maxmsg = 1;
	attr.mq_msgsize = sizeof(msgbuff_t);
	attr.mq_flags = 0;
    
    mq_unlink("/retira");
    mq_unlink("/acorda");
	fd2 = mq_open("/retira", O_RDWR|O_CREAT, 0666, &attr);
    fd1 = mq_open("/acorda", O_RDWR|O_CREAT, 0666, &attr);

    //Inicialização dos javalis
    printf("Cozinheiro encheu o caldeirão com %d javalis e foi nanar\n", MAX_NUM_JAVALIS);
    retira->controle = MAX_NUM_JAVALIS;
    mq_send(fd2, (void*)retira, sizeof(msgbuff_t), 0);

    while(1){
        mq_receive(fd1, (void*)acorda, sizeof(msgbuff_t), 0); //Lê do buffer
        if(acorda->controle == 1){ //
            printf("Cozinheiro encheu o caldeirão com %d javalis e foi nanar.\n", MAX_NUM_JAVALIS);
            mq_send(fd2, (void*)retira, sizeof(msgbuff_t), 0);
            acorda->controle = 0;
        }
    }
}
// gcc Cozinheiro.c -o Cozinheiro -lpthread -lrt 
// ./Cozinheiro
// /mnt/c/Users/bruno/OneDrive/'Área de Trabalho'/UTFPR/'7º Período'/SO25CP/Trabalhos/SO25CP/'Trabalho 9'  
// /media/brunoduarte/Acer/Users/bruno/OneDrive/'Área de Trabalho'/UTFPR/'7º Período'/SO25CP/Trabalhos/SO25CP/'Trabalho 9'