/* 4. Com base no programa do item 3, escreva outro programa em C que:
a. Após ter um vetor de tamanho n passado pelo usuário e preenchido com os
valores de índices em ordem decrescente, imprima o vetor do fim para o
começo, isto é, apresente o vetor na tela da posição n-1 até a posição 0. */

#include<stdio.h>

#define MAX 1024

int main(){
    int n, i, v[MAX];
  
    do {
        printf("Digite o valor de n, com n variando de 0 ate 1024: ");
        scanf("%d", &n);
    } while (n > 1024);

    //preenche cada elemento com n - i
    for(i = 0; i < n; i++) v[i] = n-i-1;

    for(i = n-1; i >= 0; i--) printf("%d ", v[i]);
    printf("\n");
    
    return 0;
}


