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
#include <pthread.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MAX_NUM_JAVALIS 19
#define NUM_GAULESES 5

typedef struct _pipe1_t{
    int numJavalis;
}pipe1_t;

typedef struct _pipe2_t{
    char controle;
}pipe2_t;

pipe1_t jav;
pipe2_t pedido;
int fd[2];

int main(){
    int flag = 0;
    mkfifo("retirar", 0666);
    mkfifo("servir", 0666);
    fd[0] = open("retirar", O_RDONLY);
    fd[1] = open("servir", O_WRONLY);
    jav.numJavalis = MAX_NUM_JAVALIS;
    printf("Cozinheiro encheu o caldeirão com %d javalis e foi nanar\n", jav.numJavalis);
    
    write(fd[1], &jav, sizeof(pipe1_t)); //Avisa que encheu
    while(1){
        read(fd[0], &pedido, sizeof(pipe2_t)); //Lê o controle
        if(pedido.controle == 'E'){
            //printf("Entrei");
            jav.numJavalis = MAX_NUM_JAVALIS; 
            printf("Cozinheiro encheu o caldeirão com %d javalis e foi nanar.\n", jav.numJavalis);
            write(fd[1], &jav, sizeof(pipe1_t)); //Avisa que encheu
            read(fd[0], &pedido, sizeof(pipe2_t));
        }
        if(pedido.controle == 'B'){
            jav.numJavalis--;
        }
        write(fd[1], &jav, sizeof(pipe1_t));
    }
    
}

// gcc Cozinheiro.c -o Cozinheiro -lpthread -lrt 
// ./Cozinheiro
// /mnt/c/Users/bruno/OneDrive/'Área de Trabalho'/UTFPR/'7º Período'/SO25CP/Trabalhos/SO25CP/'Trabalho 8'
// /media/brunoduarte/Acer/Users/bruno/OneDrive/'Área de Trabalho'/UTFPR/'7º Período'/SO25CP/Trabalhos/SO25CP/'Trabalho 8'