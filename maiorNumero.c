/* programa maiorNumero */
#include<stdio.h>
#define n 10

typedef int Vetor[n];
Vetor A = {50, 30, 0, 40, 21, 99, 100, 2, 9, 65};
int i, indice, maior;

/* Dado um vetor de entrada, encontra o maior elemento */
int Max(Vetor A) {
    int i, maior;
    maior = A[0];
    for (i = 1; i < n; i++) {
        if (maior < A[i]) {
            maior = A[i];
            indice = i;
        }
    }
    return maior;
}

int main() {
    printf("Vetor para busca:\n");
        for (i = 0; i < n; i++)
            printf("%10d\n", A[i]);
    maior = Max(A);
    printf("\nPressione ENTER para continuar...\n");
    getchar();
    printf("Maior elemento = %d\n", maior);
    printf("Indice do vetor = %d\n", indice);
    return 0;
}
