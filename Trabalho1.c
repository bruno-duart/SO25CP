#include <stdio.h>
#include <unistd.h>

void main(void) {
    char str[5] = "BRUNO";
    int i = 0;
    __pid_t mypid;

    printf("proc-%c, pid %d, ppid %d, acaba de ser criado\n", str[i], getpid(), getppid());//B
    mypid = fork();
    if(mypid == 0){
        i++;
        printf("proc-%c, pid %d, ppid %d, acaba de ser criado\n", str[i], getpid(), getppid());//R
        mypid = fork();
        if(mypid == 0){
            i++;
            printf("proc-%c, pid %d, ppid %d, acaba de ser criado\n", str[i], getpid(), getppid());//U
        }
        else if(mypid > 0){
            mypid = fork();
            if(mypid == 0){
                i += 2;
                printf("proc-%c, pid %d, ppid %d, acaba de ser criado\n", str[i], getpid(), getppid());//N
                mypid = fork();
                if(mypid == 0){
                    i++;
                    printf("proc-%c, pid %d, ppid %d, acaba de ser criado\n", str[i], getpid(), getppid());//O
                }
            }wait();
        }
    }
    wait();
    printf("proc-%c, pid %d morreu\n", str[i], getpid());
}