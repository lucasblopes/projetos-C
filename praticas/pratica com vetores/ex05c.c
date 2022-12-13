/* c. Calcule a média dos elementos de um vetor e a apresente na tela. */

#include<stdio.h>

#define n 10

int main(){
    int soma, i, A[n] = {0,1,2,3,4,5,6,7,8,9};
    float media;
    soma = 0;
    for(i = 0; i < n; i++) soma += A[i];
    for(i = 0; i < n; i++) printf("%d ", A[i]);
    printf("\n");
    media = (float)soma/n;
    printf("%f\n", media);
    return 0;
}
