/* 7. Escreva um programa em C que conte quantos elementos distintos há em um vetor e
apresente cada elemento e sua frequência como saída. */

#include <stdio.h>

#define MAX 1024

//insere dados no vetor
void lerVetor(int n, int *v){
    printf("Digite %d numeros: \n", n);
    for(int i = 0; i < n; i++) scanf("%d", &v[i]);
}

//imprime um vetor de tamanho n
void imprimirVetor(int n, int *v){
    for (int i = 0; i < n; i++) printf("%d ", v[i]);
    printf("\n");
}

//monta um vetor sem repeticoes
void removerRepeticoes(int n, int *index, int *v, int *vNums){
    //repetiu funciona como um boolean
    //index eh o indice do vetor vNums
    int repetiu;
    *index = 0;
    vNums[0] = v[0];
    for(int i = 1; i <= n; i++){
        repetiu = 0;
        for(int j = i-1; j >= 0; j--) if(v[i] == v[j]) repetiu++;
        if (repetiu == 0){
            (*index)++;
            vNums[*index] = v[i];
        }
    }
}

//monta o vetor vCont que armazena o numero de repeticao de cada numero do vetor original
void contarOcorrencias(int n, int index, int *v, int *vNums, int *vCont){
    for(int i = 0; i < index; i++){
        vCont[i] = 0;
        for (int j = 0; j < n; j++) if (vNums[i] == v[j]) vCont[i]++;
    }
}

//resultado final
void imprimirResultado(int index, int *vNums, int *vCont){
    for(int i = 0; i < index; i++) printf("Elemento %d apareceu %d vezes \n", vNums[i], vCont[i]);
}

int main(){
    //v -> vetor original
    //vNums -> vetor sem repeticoes
    //vCont -> vetor que armazena a ocorrencia de cada numero do vetor original
    int n, v[MAX], vNums[MAX], vCont[MAX]; 
    int index = 0;

    do {
        printf("Digite o valor de n, com n variando de 0 ate 1024: ");
        scanf("%d", &n);
    } while (n > 1024);

    lerVetor(n ,v);
    removerRepeticoes(n, &index, v, vNums);
    contarOcorrencias(n, index, v, vNums, vCont);
    imprimirVetor(n, v);
    imprimirResultado(index, vNums, vCont);


    return 0;
}
