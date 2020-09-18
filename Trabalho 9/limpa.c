#include <stdio.h>
#include <mqueue.h>

int main(){
    mq_unlink("/retira");
    mq_unlink("/acorda");
    return 0;
}