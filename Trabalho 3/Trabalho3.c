#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <unistd.h>
//#include <time.h>

#define NUM_TERMOS 1e9  //Define o número mínimo de termos a ser calculado
#define NUM_THREADS 16   //Define o número de threads
#define NUM_TER_THR NUM_TERMOS/NUM_THREADS  //Define o número de Termos Por Thread
double result_piLGM[NUM_THREADS], result_piNila[NUM_THREADS]; //Arrays para resultados parciais

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
    pthread_t thread[NUM_THREADS];//, threadNila[NUM_THREADS];
    long i, status;
    double resultLGM = 0, resultNila = 0.75; 
    //clock_t tempoLGM, tempoNila; 

    for(int l = 0; l < NUM_THREADS; l++){
        result_piNila[NUM_THREADS] = 0;
        result_piLGM[NUM_THREADS] = 0;
    }
    
    printf("Threads: %d\t(%.0lf termos)\n", NUM_THREADS, NUM_TERMOS);
    
    //Executando as threads da Série Leibniz-Gregory-Madhava
    for(i = 0; i < NUM_THREADS; i++){
        status = pthread_create(&thread[i], NULL, LGM, (void*)i);
        if(status) {
            perror("pthread_create");
            exit(1);
        }
        
    }
    for(i = 0; i < NUM_THREADS; i++){
        pthread_join(thread[i], NULL);
        resultLGM += result_piLGM[i];
    }
    printf("LGM \tTempo: 500 s \t%.15f\n", 4*resultLGM);
    
    
    //Executando as threads da Série Nilakantha
    /*for(i = 0; i < NUM_THREADS; i++){
        status = pthread_create(&thread[i], NULL, Nila, (void*)i);
        if(status) {
            perror("pthread_create");
            exit(1);
        }
    }
    for(i = 0; i < NUM_THREADS; i++){
        pthread_join(thread[i], NULL);
        resultNila += result_piNila[i];
    }
    printf("NIL \tTempo: 500 s \t%.15f\n", 4*resultNila); */

    pthread_exit(NULL);
}
//\tTempo: %.5f s  (double)tempoNila/CLOCKS_PER_SEC,