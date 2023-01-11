//alocacao dinamica de matriz
#include <stdio.h>
#include <stdlib.h>

/*Funcao calloc:
-aloca espaco de armazenamento na memoria e inicializa o espaco alocado
-entrada: numero de elementos a serem alocados e tamanho de cada elemento em byte
-retorno: ponteiro para o inicio da area de armazenamento alocado na memoria
 -area de armazenamento eh automaticamente atribuido a 0
*/

int main(){
    int **matriz;
    int nlin = 2;
    int ncol = 3;

    matriz = calloc(nlin, sizeof(int *));

    for(int i = 0; i < nlin; i++){
        matriz[i] = calloc(ncol, sizeof(int));
    }

    for(int i = 0; i < nlin; i++){
        for(int j = 0; j < ncol ; j++){
            printf("%d ", matriz[i][j]);
        }
        printf("\n  ");
    }

    return 0;
}