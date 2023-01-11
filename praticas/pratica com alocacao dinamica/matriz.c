#include<stdlib.h>
#include<stdio.h>

int main(){
    //ponteiro para ponteiro
    int **matriz;
    int nlin, ncol;
    nlin = 2;
    ncol = 3;

    //cada linha tem um ponteiro que a ponta para as colunas
    matriz = calloc(nlin, sizeof(int *));

    //alocando as colunas
    for(int i = 0; i < nlin; i++){
        matriz[i] = calloc(ncol, sizeof(int));
    }

    for(int i = 0; i < nlin; i++) {
        for(int j = 0; j < ncol; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }

    free(matriz);
    
    return 0;
}