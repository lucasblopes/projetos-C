#include<stdio.h>

#define MAX 1024

int main(){
    int n, vetor[MAX], *ptr, *fimVetor;

    do{
        printf("Digite o valor de n [1 <= n <= 1024], sendo n o tamanho do vetor:  ");
        scanf("%d", &n);
    } while (n < 1 || n > 1024);

    fimVetor = vetor + n;
    
    //entrada de dados
    printf("Digite %d numeros: \n", n);
    for(ptr = vetor; ptr < fimVetor; ptr++)
        scanf("%d", ptr);

    //impressao do vetor
    for(ptr = vetor; ptr < fimVetor; ptr++)
        printf("%d ", *ptr);
    printf("\n");

    return 0;
}