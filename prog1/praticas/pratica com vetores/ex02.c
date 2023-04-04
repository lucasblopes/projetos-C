/*
2. Com base no programa do item 1, escreva um programa em C que:
a. No item “c” do item anterior, em vez de preencher cada posição do vetor com o
valor dos índices do intervalo, preencha o vetor em modo decrescente (ex.: se n
== 10, os índices do vetor vão de 0 até 9; a posição indexada por 0 deve
receber o valor 9, posição 1 recebe 8 e assim por diante até que o índice 9
receba valor 0).*/

#include<stdio.h>
#define MAX 1024

int main(){
    int n, i, v[MAX];
  
    do {
        printf("%s", "Digite o valor de n, com n variando de 0 ate 1024: ");
        scanf("%d", &n);
    } while (n > 1024);

    //preenche cada elemento com n - i
    for(i = 0; i < n; i++) {
        v[i] = n-i-1;
        printf("%d ", v[i]);
    }
    printf("\n");
    
    return 0;
}
