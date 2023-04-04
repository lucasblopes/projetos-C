#include<stdio.h>
                                                                                                        
//OBS: int vetor[] eh interpretado como int *vetor
int somaVetor(int v[], int n){
    int soma = 0;
    int *ptr;
    int *fimVetor = v + n;

    for(ptr = v; ptr < fimVetor; ptr++)
        soma += *ptr;
        
    return soma;
}

int main(){
    int valores[10] = {1,2,3,4,5,6,7,8,9,10};
    printf("A soma dos valores do vetor é = %d\n", somaVetor(valores,10));
    return 0;
}