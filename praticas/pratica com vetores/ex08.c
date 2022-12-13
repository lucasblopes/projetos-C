/* 8. Escreva um progama em C no qual, dados dois vetores do mesmo tamanho,
concatenar-os em um terceiro vetor. */

#include <stdio.h>

#define MAX 1024

//insere dados no vetor
void lerVetor(int n, int *v){
    printf("Digite %d numeros: \n", n);
    for(int i = 0; i < n; i++) scanf("%d", &v[i]);
}

//printa o vetor
void imprimirVetor(int n, int *v){
    for(int i = 0; i < n; i++) printf("%d ", v[i]);
    printf("\n");
}

//monta o terceiro vetor concatenando o v1 com o v2
void concatenarVetores(int n, int m, int *v1, int *v2, int *v3){
    for(int i = 0; i < m; i++){
        if(i < n) v3[i] = v1[i];
        else v3[i] = v2[i-n];
    }
}

int main(){
    int n, m, v1[MAX], v2[MAX], v3[MAX]; 

    do {
        printf("Digite o valor de n, com n variando de 0 ate 1024: ");
        scanf("%d", &n);
    } while (n > 1024);
    //tamanho do terceiro vetor eh o dobro de v1 e de v2
    m = 2*n;

    printf("v1: ");
    lerVetor(n, v1);
    printf("v2: ");
    lerVetor(n, v2);
    concatenarVetores(n, m, v1, v2, v3);
    printf("v3: ");
    imprimirVetor(m, v3);

    return 0;
}