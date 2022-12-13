/* 3. Com base no programa do item 1, escreva um programa em C que:
a. No item “c”, receba do usuário cada valor a ser indexado no intervalo [0, n);
b. Imprima o vetor recebido em ordem. */

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
        printf("Digite um numero: ");
        scanf("%d\n", &v[i]);
    }
    
    for(i = 0; i < n; i++) printf("%d ", v[i]);
    printf("\n");
    
    return 0;
}
