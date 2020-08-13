/*
 ****************************************************
 *         Sistemas Operacionais - 2020/1           *
 *             Trabalho 8 - Jantar dos              *
 *                 Gauleses (PIPES)                 *
 *              Bruno Duarte  1917323               *
 *          brunoduarte@alunos.utfpr.edu.br         *
 ****************************************************
*/
//Código fonte principal


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(){
    pid_t pid;

    pid = fork();
    if(pid > 0){
        system("gcc Cozinheiro.c -o coz -lpthread");
        execl("./coz", "", NULL);
    } else if (pid == 0){
        system("gcc Gaules.c -o gau -lpthread");
        execl("./gau", "", NULL);
    } else{
        printf("Erro\n");
    }
    exit(0);
}

