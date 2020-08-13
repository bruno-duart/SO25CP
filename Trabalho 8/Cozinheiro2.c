// gcc Cozinheiro2.c -o Cozinheiro2 -lpthread -lrt 
// ./Cozinheiro2
// /mnt/c/Users/bruno/OneDrive/'Área de Trabalho'/UTFPR/'7º Período'/SO25CP/Trabalhos/SO25CP/'Trabalho 8'
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

typedef struct _pipe2_t{
    char controle;
}pipe_t;

pipe_t pedido;
int fd[2];
pipe_t *gau, *coz;

int main(){
    pipe_t gauLocal, cozLocal;
    gau = &gauLocal;
    coz = &cozLocal;
    pid_t pid;
    mkfifo("retirar", O_CREAT|O_EXCL);
    mkfifo("servir", O_CREAT|O_EXCL);
    fd[0] = open("retirar", O_RDONLY);
    fd[1] = open("servir", O_WRONLY);

    printf("Cozinheiro encheu o caldeirão com %d javalis e foi nanar\n", MAX_NUM_JAVALIS);
    coz->controle = 'J';
    for(int i = 0; i < MAX_NUM_JAVALIS; i++)
        write(fd[1], coz, sizeof(pipe_t));
    coz->controle = 'V';  
    write(fd[1], coz, sizeof(pipe_t));
    
    while(1){
        read(fd[0], gau, sizeof(pipe_t)); //Lê o controle
        if(gau->controle == 'E'){
            printf("Entrei");
            coz->controle = 'J';
            printf("Cozinheiro encheu o caldeirão com %d javalis e foi nanar.\n", MAX_NUM_JAVALIS);
            for(int i = 0; i < MAX_NUM_JAVALIS; i++)
                write(fd[1], coz, sizeof(pipe_t));
            coz->controle = 'V';  
            write(fd[1], coz, sizeof(pipe_t)); //Avisa que encheu
        }
    }   
}
