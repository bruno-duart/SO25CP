/*
 ****************************************************
 *         Sistemas Operacionais - 2020/1           *
 *             Trabalho 12 - Jantar dos             *
 *        Gauleses  (Passagem de mensagens)         *
 *              Bruno Duarte  1917323               *
 *          brunoduarte@alunos.utfpr.edu.br         *
 ****************************************************
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <mqueue.h>

int main(){
	pid_t pid;

    pid = fork();
	if(pid > 0){
		system("gcc Cozinheiro2.c -o coz -lrt");
		execl("./coz","", NULL);
	} else if (pid == 0) {

		sleep(1);
		system("gcc Gaules2.c -o gau -lpthread -lrt ");
		execl("./gau","", NULL);
	} else {
		printf("Erro\n");
	}
	exit(0);
}

// gcc main.c -o main -lpthread -lrt
// ./main