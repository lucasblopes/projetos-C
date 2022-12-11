#include<stdio.h>

void troca(int *a, int *b){
    int aux;
    aux = *a;
    *a = *b;
    *b = aux;
}

int main(){
    int a, b;
    printf("Digite os valores de a e b: \n");
    scanf("%d", &a);
    scanf("%d", &b);
    troca(&a, &b);
    printf("a = %d, b = %d\n", a , b);
    return 0;
}