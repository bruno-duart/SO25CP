#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#define RAND_DIVISOR 10000

#define N 5 // Lucas tem 5 letras
#define M 19 // O 'buffer' da mesa tem 19 posições
 
sem_t mesa, coz_status, gaules_status;
//sem_t s[N];

int n_javalis;
 
char Nome(int tid){
	if(tid == 0)
		return('L');
	if(tid == 1)
		return('U');
	if(tid == 2)
		return('C');
	if(tid == 3)
		return('A');
	if(tid == 4)
		return('S');
}



void *Gaules(void *threadid){
    long tid = (long) threadid, i;
	while(1){
		sleep(1);
		if(n_javalis == 0){
			sem_post(&coz_status); // acorda o cozinheiro
			printf("\nSou o Gaulês %c(%ld) e estou acordando o cozinheiro pois não há nenhum javali.", Nome(tid), tid);
			//sem_wait(&gaules_status); // Espera o gaulês comer
		}
		sem_wait(&mesa); // Solicita acesso à mesa
		sem_wait(&gaules_status);
		n_javalis--;
		sem_post(&gaules_status);
		printf("\nSou o Gaulês %c(%ld) e estou comendo. Restam %2d javalis na mesa.", Nome(tid), tid, n_javalis);
		sem_post(&mesa);
	}
}

void ColocaJavalis(){
	printf("\nSou o cozinheiro e a mesa está posta. Restam 19 javalis na mesa.");
	n_javalis = M; // Repõe os M javalis na mesa
}

void *Cozinheiro(){
	while(1){
		sleep(1);
		sem_wait(&coz_status); // Cozinheiro dorme
		ColocaJavalis(); // Repõe a mesa
		printf("\n\t\t\t*O cozinheiro dormiu.*");
		sem_post(&mesa); // Libera a mesa
	}
}

int main(){
	sem_init(&mesa, 0, 1); // Inicialmente a mesa pode ser acessada
	sem_init(&coz_status, 0, 0); // Inicialmente o cozinheiro está dormindo
	sem_init(&gaules_status, 0, 1); // Inicialmente o gaulês não está esperando
	pthread_t thread_G[N], thread_C;
	n_javalis = M;
	for(long i = 0; i < N; i++){
		pthread_create(&thread_G[i], NULL, Gaules, (void *) i);
	}
	pthread_create(&thread_C, NULL, &Cozinheiro, NULL);

	for(int i = 0; i < N; i++)
		pthread_join (thread_G[i], NULL);
	exit(0);
}