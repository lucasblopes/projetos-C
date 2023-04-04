#include <stdio.h>
#include <stdlib.h>

void imprimirVetor(int* v, int n){

    int i;
    for(i = 0; i < n; i++)
        printf("%d ", v[i]);
    printf("\n");
}

void gerarSubConjuntos(int* v, int* vRes, int i, int n){

    if (i == n){
        for(int i = 0; i < n; i++)
            vRes[i] = v[i]*(i+1);
        imprimirVetor(vRes, n);
        return;
    }
    v[i] = 0;
    gerarSubConjuntos(v, vRes, i+1, n);
    v[i] = 1;
    gerarSubConjuntos(v, vRes, i+1, n);
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
    int* vRes = malloc(n * sizeof(int));
        if(!vRes){
            printf("Erro em malloc\n");
            return 1;
        }

    gerarSubConjuntos(v,vRes, i, n);
    free(v);

    return 0;
}