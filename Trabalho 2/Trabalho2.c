/*
 ****************************************************
 *         Sistemas Operacionais - 2020/1           *
 *              Trabalho 2 - SYSCALLS               *
 *              Bruno Duarte  1917323               *
 *          brunoduarte@alunos.utfpr.edu.br         *
 ****************************************************
*/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int count, flag = 0;
char ans;
void sigint_handler(){
    count++;
}
void sigtstp_handler(){
    flag = 1;
}
void sigalrm_handler(){
    if(ans != 'n')
        kill(getpid(), SIGKILL);
    ans = ' ';
}
int main(){
    signal(SIGINT, sigint_handler);
    signal(SIGTSTP, sigtstp_handler);
    signal(SIGALRM, sigalrm_handler);
    ans = ' ';
    count = 0;

    while(1){
        if(flag){
            printf("\nNumber of SIGINTS: %d\n", count);
            flag = 0;
        }
        if(count == 10){
            printf("\n");
            printf("Do you really want to exit (Y/n)? ");
            alarm(5);
            scanf(" %c", &ans);
            if(ans == 'Y'){
                kill(getpid(), SIGKILL);
            } else if(ans == 'n'){
                count = 0;
            }
        }
    }
    return 0;
}