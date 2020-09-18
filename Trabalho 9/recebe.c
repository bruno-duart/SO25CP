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
    mqd_t fd;

   // mq_unlink("/myqueue");
    fd = mq_open("/myqueue", O_RDWR);

    for(;;){
        mq_receive(fd, (void*)ptr, sizeof(msg_t), 0);
        printf("Recebendo %d e %f\n", ptr->a, ptr->v);
        sleep(1);
    }

    return 0;
}