/* 10. Escreva um programa em C que, dado um vetor preenchido, imprime a quantidade de
elementos pares e ímpares. */

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

//conta quantos numeros pares e impares existem no vetor
void contarImparesePares(int n, int *contImp, int *contPar, int *v){
    for(int i = 0; i < n; i++){
        if(v[i] % 2 == 1) (*contImp)++;
        else (*contPar)++;
    }
}

int main(){
    int n, m, v[MAX];
    int contImp, contPar = 0;

    do {
        printf("Digite o valor de n, com n variando de 0 ate 1024: ");
        scanf("%d", &n);
    } while (n > 1024);

    lerVetor(n, v);
    contarImparesePares(n, &contImp, &contPar, v);
    imprimirVetor(n, v);
    printf("Quantidade de numeros impares: %d\n", contImp); 
    printf("Quantidade de numeros pares: %d\n", contPar);

    return 0;
}
