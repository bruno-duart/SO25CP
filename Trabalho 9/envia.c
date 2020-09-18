#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

typedef struct msg_{
    int a;
    float v;
}msg_t;

int main(){
    msg_t data;
    msg_t *ptr = &data;
    struct mq_attr attr;
    mqd_t fd;

    attr.mq_maxmsg = 10;
    attr.mq_msgsize = sizeof(msg_t);
    attr.mq_flags = 0;

    mq_unlink("/myqueue");
    fd = mq_open("/myqueue", O_RDWR|O_CREAT, 0666, &attr);

    for(;;){
        ptr->a = rand()%1000;
        ptr->v = rand()/((double)RAND_MAX);

        mq_send(fd, (void*)ptr, sizeof(msg_t), 0);
        printf("Enviando %d e %f\n", ptr->a, ptr->v);
        sleep(1);
    }

    return 0;
}