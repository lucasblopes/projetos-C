/* 9. Escreva um programa em C que mostre, para um dado vetor:
a. Quantos e quais são os elementos repetidos neste vetor; */

#include <stdio.h>

#define MAX 1024

//insere dados no vetor
void lerVetor(int n, int *v){
    printf("Digite %d numeros: \n", n);
    for(int i = 0; i < n; i++) scanf("%d", &v[i]);
}

//imprime o vetor
void imprimirVetor(int n, int *v){
    for(int i = 0; i < n; i++) printf("%d ", v[i]);
    printf("\n");
}

//cria um vetor com os numeros que se repetem
void checarNumerosRepetidos(int n, int *index, int *v, int *vReps){
    int cont, considerado = 0; //considerado funciona como um boolean
    *index = 0;
    for(int i = 0; i < n-1; i++){
        considerado = 0;
        for(int j = i + 1; j < n; j++){
            for(int k = 0; k < *index; k++){
                if(i != 0 && v[i] == v[k]) considerado++;
            }
            if (considerado == 0){
                if(v[i] == v[j]){
                    vReps[*index] = v[i];
                    (*index)++;
                    considerado++;
                }
            }
        }
    }
}

//conta quantos elementos repetidos o vetor possui
int qtdRepeticoes(int n, int index, int *v, int *vReps){
    int cont = 0;
    for(int i = 0; i < index; i++){
        for(int j = 0; j < n; j++){
            if (vReps[i] == v[j]) cont++;
        }
    }
    return cont;
}

int main(){
    //v -> vetor original
    //vReps -> vetor dos numeros repetidos
    int n, index, v[MAX], vReps[MAX];

    do {
        printf("Digite o valor de n, com n variando de 0 ate 1024: ");
        scanf("%d", &n);
    } while (n > 1024);

    lerVetor(n, v);
    imprimirVetor(n, v);
    checarNumerosRepetidos(n, &index, v, vReps);
    printf("Quantidade de numeros repetidos: %d\n", qtdRepeticoes(n, index, v, vReps));
    printf("Numeros repetidos: ");
    imprimirVetor(index, vReps);

    return 0;
}