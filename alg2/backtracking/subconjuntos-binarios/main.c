#include <stdio.h>
#include <stdlib.h>

void imprimirVetor(int* v, int n){

    int i;
    for(i = 0; i < n; i++)
        printf("%d ", v[i]);
    printf("\n");
}

void gerarSubConjuntos(int* v, int i, int n){

    //printf("i = %d\n", i);
    if (i == n){
        imprimirVetor(v, n);
        return;
    }
    v[i] = 0;
    gerarSubConjuntos(v, i+1, n);
    v[i] = 1;
    gerarSubConjuntos(v, i+1, n);
}

int main(){

    int n = 0,
        i = 0;

    printf("n = ");
    scanf("%d", &n);

    int* v = malloc(n * sizeof(int));
        if(!v){
            printf("Erro em malloc\n");
            return 1;
        }

    //preencherZeros(v, n);
    gerarSubConjuntos(v, i, n);
    free(v);

    return 0;
}