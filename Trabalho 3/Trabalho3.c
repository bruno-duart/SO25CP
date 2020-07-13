#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

double NUM_TERMOS = 1000; //Define o número mínimo de termos a ser calculado

/*  Séries para aproximação de PI
 *  Euler: 
 *   pi = 2 * (1 + (1/3) + ((1*2)/(3*5)) + ((1*2*3)/(3*5*7)) )
 *   pi = 2 * (1 + sum(n! / (produtorio(2m + 1))))
 *                               m: 1 ~ n
 *                     n: 1 ~ infinity
 *
 *  Nilakantha:
 *   pi = 4 * [(3/4) + (1/(2*3*4)) - (1/(4*5*6)) + (1/(6*7*8)) ]
 *   pi = 4 * [(3/4) + sum( [(-1)^(n+1)] * [1/((2*n)*(2*n + 1)*(2 * n + 2))] ) ]
 *  **/

//Declaração dos Arrays
double resultEuler;



// Funções para o cálculo dos termos

//Cálculo do fatorial
double fatorial(double n){
    double fat = 1;
    
    for(double i = n; i > 0; i--){
        fat *= i;
    }

    return fat;
}
//Cálculo de cada termo
double termoEuler(double n){
    double produt = 1;

    for(double i = 1; i <= n; i++){
        produt *= 2*i + 1;
    }

    return (fatorial(n) / produt);
}
/*Soma dos resultados parciais
double somaEuler(){
    double resultado = 1;

    for(int i = 0; i < NUM_TERMOS; i++){
        resultado += resultEuler[i];
    }
    return 2.0*resultado;
}*/
int main(){
    resultEuler = 1;
    
    for(int i = 0; i < NUM_TERMOS; i++){
        resultEuler += termoEuler((double)i+1);
    }
    
    printf("Aproximação de Euler para pi com %lf termos: %f\n", NUM_TERMOS, 2*resultEuler);
    //free(resultEuler);
    return 0;
}