/* 6. Escreva um programa em C no qual, dados dois vetores de mesmo tamanho,
multiplique cada posição de cada vetor e guarde o produto em um terceiro vetor. */

#include <stdio.h>

#define MAX 1024

//entrada de dados em um vetor de tamanho n
void lerVetor(int n, int *v){
    int j;
    for(j = 0; j < n; j++) scanf("%d", &v[j]);
}

//imprime um vetor de tamanho n
void imprimirVetor(int n, int *v){
    for (int i = 0; i < n; i++) printf("%d ", v[i]);
    printf("\n");
}

int main(){
    int n, i, v1[MAX], v2[MAX], v3[MAX];

    do {
        printf("Digite o valor de n, com n variando de 0 ate 1024: ");
        scanf("%d", &n);
    } while (n > 1024);

    printf("Digite %d valores para o primeiro vetor: \n", n);
    lerVetor(n, v1);

    printf("Digite %d valores para o segundo vetor: \n", n);
    lerVetor(n, v2);

    printf("v1: ");
    imprimirVetor(n, v1);
    printf("v2: ");
    imprimirVetor(n, v2);

    //preenche o vetor 3, no qual cada elemento resulta da multiplicacao dos elementos de v1 e de v2
    for (i = 0; i < n; i++) v3[i] = v1[i]*v2[i];

    printf("v3: ");
    imprimirVetor(n, v3);
    
    return 0;
}