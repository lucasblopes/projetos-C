/* 1. Escreva um programa em C que:
a. Receba um inteiro n do usuário;
b. Crie um vetor de tamanho n, desde que n seja igual ou menor do que 1024;
c. Preencha cada posição do vetor com o valor dos índices do intervalo;
d. LEMBRETE: o tamanho máximo do vetor deve ser ESTÁTICO! */

#include<stdio.h>
#define MAX 1024

int main(){
    int n, i, v[MAX];
  
    do {
        printf("Digite o valor de n, com n variando de 0 ate 1024: ");
        scanf("%d", &n);
    } while (n > 1024);

    //preenche cada elemento com o seu indice
    for(i = 0; i < n; i++) {
        v[i] = i;
        printf("%d ", v[i]);
    }
    printf("\n");
    
    return 0;
}