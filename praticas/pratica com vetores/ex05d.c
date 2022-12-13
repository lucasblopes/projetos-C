/* d. Imprime o maior e o menor elemento deste vetor. */

#include<stdio.h>

#define n 10

int main(){
    int maior, menor, A[n] = {10, 25, 43, 67, 13, 3, 6, 13, 22, 11};
    maior, menor = A[0];

    for(int i = 0; i < n; i++) {
        if (A[i] > maior) maior = A[i];
        if (A[i] < menor) menor = A[i];
    }

    for(int i = 0; i < n; i++) printf("%d ", A[i]);
    printf("\n");
    printf("menor valor = %d\n", menor);
    printf("maior valor = %d\n", maior);

    return 0;
}