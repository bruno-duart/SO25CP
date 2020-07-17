#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define NUM_TERMOS 1e9  //Define o número mínimo de termos a ser calculado
int NUM_THREADS[5] = {1, 2, 4, 8, 16};   //Define o número de threads
int NUM_TER_THR;  //Define o número de Termos Por Thread
double *result_piLGM, *result_piNila; //Arrays para resultados parciais

// gcc Trabalho3.c -o Trabalho3 -lm -lpthread && ./Trabalho3 >> ResultadosMeuPc.txt

/*  Séries para aproximação de PI
 *  Nilakantha:
 *   pi = 4 * [(3/4) + (1/(2*3*4)) - (1/(4*5*6)) + (1/(6*7*8)) ]
 *   pi = 4 * [(3/4) + sum( [(-1)^(n+1)] * [1/((2*n)*(2*n + 1)*(2 * n + 2))] ) ]
 *  
 *  Leibniz-Gregory-Madhava
 *   pi = 4 * (1 - 1/3 + 1/5 - 1/7 + 1/)
 * **/

// Funções para o cálculo dos termos
double termoLGM(double n){
    return pow(-1, n) * 1/(2*n + 1);
}

double termoNila(double n){
    if((int)n % 2 != 0)
        return (double)1/(2*n * (2*n + 1) * (2*n + 2));
    return (double)-1/(2*n * (2*n + 1) * (2*n + 2));
}

void *LGM(void *threadID){
    long tid = (long)threadID;
    for(long i = tid*NUM_TER_THR; i < tid*NUM_TER_THR + NUM_TER_THR; i++)
        result_piLGM[tid] += termoLGM((double)i);
    pthread_exit(NULL);
}

void *Nila(void *threadID){
    long tid = (long)threadID;
    for(long i = tid*NUM_TER_THR; i < tid*NUM_TER_THR + NUM_TER_THR; i++)
        result_piNila[tid] += termoNila((double)i+1);
    pthread_exit(NULL);
}

void main(void){
    
    long i, status;
    double resultLGM = 0, resultNila = 0; 
    clock_t tempoLGM, tempoNila; 
    for(int idx = 0; idx < 5; idx++){
        result_piLGM = malloc(sizeof(double) * NUM_THREADS[idx]);
        result_piNila = malloc(sizeof(double) * NUM_THREADS[idx]);
        NUM_TER_THR = NUM_TERMOS / NUM_THREADS[idx];
        printf("Threads: %d\t(%.0lf termos)\n", NUM_THREADS[idx], NUM_TERMOS);
        pthread_t thread[NUM_THREADS[idx]];//, threadNila[NUM_THREADS];
        
        //Executando as threads da Série Leibniz-Gregory-Madhava
        tempoLGM = clock();
        for(i = 0; i < NUM_THREADS[idx]; i++){
            status = pthread_create(&thread[i], NULL, LGM, (void*)i);
            if(status) {
                perror("pthread_create");
                exit(1);
            }
            
        }
        for(i = 0; i < NUM_THREADS[idx]; i++){
            pthread_join(thread[i], NULL);
            resultLGM += result_piLGM[i];
        }
        tempoLGM = clock() - tempoLGM;    
        printf("LGM \tTempo: %.5f s \t%.15f\n", (double)tempoLGM/CLOCKS_PER_SEC, 4*resultLGM);

        //Executando as threads da Série Nilakantha
        tempoNila = clock();
        for(i = 0; i < NUM_THREADS[idx]; i++){
            status = pthread_create(&thread[i], NULL, Nila, (void*)i);
            if(status) {
                perror("pthread_create");
                exit(1);
            }
        }
        for(i = 0; i < NUM_THREADS[idx]; i++){
            pthread_join(thread[i], NULL);
            resultNila += result_piNila[i];
        }
        tempoNila = clock() - tempoNila;    
        printf("NIL \tTempo: %.5f s \t%.15f\n", (double)tempoNila/CLOCKS_PER_SEC, 4*resultNila + 3);
    }
    pthread_exit(NULL);
}