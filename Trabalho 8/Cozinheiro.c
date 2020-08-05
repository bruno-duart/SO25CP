#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/stat.h>

#define MAX_NUM_JAVALIS 19
#define NUM_GAULESES 5

typedef struct _pipe1_t{
    int numJavalis;
}pipe1_t;

typedef struct _pipe2_t{
    char comando;
}pipe2_t;

pipe1_t *jav;
pipe2_t *cont;


int main(){
    
    jav->numJavalis = MAX_NUM_JAVALIS;
    printf("Cozinheiro encheu o caldeirão com %d javalis e foi nanar\n", jav->numJavalis);
    while(1){
        read(); //Lê o controle
        if(cont->comando== 'E'){
            jav->numJavalis = MAX_NUM_JAVALIS; 
            printf("Cozinheiro encheu o caldeirão com %d javalis e foi nanar.\n", controle->numJavalis);
            write(); //Avisa que encheu
        }
        if(cont->comando == 'B'){
            jav->numJavalis--;
        }
        write();
    }
}

// gcc Cozinheiro.c -o Cozinheiro -lpthread -lrt 
// ./Cozinheiro