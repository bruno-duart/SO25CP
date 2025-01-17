#include <stdio.h>

/*
    SÉRIES PARA APROXIMAÇÃO DE PI

1ª: pi = 4 * (1 - 1/3 + 1/5 - 1/7 + 1/9 - 1/11 + ...)

    pi = 4 * somatorio((-1)^n/(2n + 1))
             n: 0 ~ infinito


2ª: pi = 2 * (1 + 1/3 + (1*2)/(3*5) +  (1*2*3)/(3*5*7))

    pi = 2 * (1 + sum(n!/(produtorio(2m + 1)))
                          m: 1 ~ n
                  n: 1 ~ infinito

*/

// retorna o fatorial de um inteiro
double fatorial(int n){
    int i;
    double fat = 1;
    if(n < 0)
        fat = 0;
    else{
        for(i = 1; i <= n; i++)
            fat *= i;
    }
    return fat;
}

// retorna o produtório (2m + 1), com m variando de 1 a n
double produtorio_2(int lim_inf, int lim_sup){
    int i;
    double prod = 1;
    for(i = lim_inf; i <= lim_sup; i++){
        prod *= (2 * i + 1);
    }
    return prod;
}
double fator_soma(int pot){
    if(pot % 2 == 0)
        return 1;
    else
        return -1;
}

// retorna o somatório dos n primeiros termos da primeira série para aproximação de pi
double pi_1(int n){
    int i;
    double sum = 0;
    for(i = 0; i <= n; i++){
        sum += (fator_soma(i)/(2*i + 1));
    }
    return 4*sum;
}

double pi_2(int n){
    int i;
    double sum = 1;
    for(i = 1; i<= n; i++){
        sum += (fatorial(i)/produtorio_2(1, i));
    }
    return 2*sum;
}

int main(){
    int n = 1000;

    printf("%lf", pi_2(n));

    return 0;
}