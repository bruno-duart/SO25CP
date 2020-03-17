#include <stdio.h>
#include <unistd.h>

int main(void) {
    char str[100];
    int i = 0;
    __pid_t mypid;

    scanf("%s", str);
    printf("proc-%c, pid %d, ppid %d, acaba de ser criado\n", str[i], getpid(), getppid());
    if(fork() == 0){
        i++;
        printf("proc-%c, pid %d, ppid %d, acaba de ser criado\n", str[i], getpid(), getppid());

        if(fork() == 0){
            i++;
            printf("proc-%c, pid %d, ppid %d, acaba de ser criado\n", str[i], getpid(), getppid());

            if(fork() == 0){
                i++;
                printf("proc-%c, pid %d, ppid %d, acaba de ser criado\n", str[i], getpid(), getppid());
            }
        }
        wait();
        if(fork() == 0){
            i++;
            printf("proc-%c, pid %d, ppid %d, acaba de ser criado\n", str[i], getpid(), getppid());
        }
    }
    wait();
    printf("proc-%c, pid %d morreu\n", str[i], getpid());
}