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
            printf("Number of SIGINTS: %d\n", count);
            flag = 0;
        }
        if(count == 10){
            printf("\n");
            printf("Do you want to exit (Y/n)? ");
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