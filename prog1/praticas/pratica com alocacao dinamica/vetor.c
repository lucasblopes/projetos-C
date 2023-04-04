#include<stdio.h>
#include<stdlib.h>

int main(){
    //alocacao dinamica de vetor
    int *a; //ponteiro de inteiro
    a = malloc(10*sizeof(int)); //alocando 10 espacos na memoria para a
    printf("Digite 10 numeros:\n");
    for(int i = 0; i < 10; i++)
        scanf("%d", &a[i]);
    
    printf("Vetor a:\n");
    for(int i = 0; i < 10; i++)
        printf("%d ", a[i]);
    printf("\n");

    free(a);
    
    return 0;
}