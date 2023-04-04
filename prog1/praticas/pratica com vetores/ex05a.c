/* 5. Escreva um programa em C para cada um dos itens abaixo:
a. Um vetor preenchido é copiado em ordem inversa em um outro vetor. */

#include<stdio.h>

#define n 10

int main(){
    int B[n], i, A[n] = {0,1,2,3,4,5,6,7,8,9};
    //copia A em ordem inversa em B
    for(i = 1; i < n; i++) {
        B[i] = A[n-i];
        printf("%d ", B[i]);
    }
    printf("\n");
    return 0;
}
