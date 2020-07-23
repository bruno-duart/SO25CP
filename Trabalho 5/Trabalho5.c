#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>

#define NUM_THREADS 3
#define NUM_SEMAPHORES 9
sem_t s[NUM_SEMAPHORES];
int x, y, z, h, j, u;
/* s[0] -> procA
 * procA -> s[1] -> procB -> procC 
 * procA -> s[2] -> procG
 * 
 * procE -> s[3] -> procD
 * procC ->  ---|
 * 
 * procE -> s[4] -> procH
 * procG -> ---|
 * 
 * procD -> s[5] -> procF
 * procH -> s[6] ---|
 * */
void *P1(void *tid){
    sem_wait(&s[0]);
    x = 1;
    y = 1;
    z = 2;
    sem_post(&s[1]);
    sem_post(&s[2]);
    y += 2;
    sem_post(&s[3]);
    sem_post(&s[4]);
    sem_wait(&s[5]);
    sem_wait(&s[6]);
    u = h + j / 3;
}
void *P2(void *tid){
    sem_wait(&s[1]);
    x *= 2;
    x += 1;
    sem_wait(&s[3]);
    h = y + x;
    sem_post(&s[5]);
}
void *P3(void *tid){
    sem_wait(&s[2]);
    z /= 2;
    sem_wait(&s[4]);
    j = z + y - 4;
    sem_post(&s[6]);
}

int main(){
    pthread_t thread[NUM_THREADS];

    sem_init(&s[0], 0, 1);
    for(int i = 1; i < NUM_SEMAPHORES; i++)
        sem_init(&s[i], 0, 0);

    pthread_create(&thread[0], NULL, P1, NULL);
    pthread_create(&thread[1], NULL, P2, NULL);
    pthread_create(&thread[2], NULL, P3, NULL);

    pthread_join(thread[0], NULL);
    pthread_join(thread[1], NULL);
    pthread_join(thread[2], NULL);
    
    printf("Valor final de u: %d\n", u);
    pthread_exit(NULL);
}