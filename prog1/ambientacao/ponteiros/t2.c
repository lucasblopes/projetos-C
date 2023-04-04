#include<stdio.h>

int main(){
    int valores[3] = {1,2,5};
    printf("%d\n", *(valores + 2)); //acessa o elemento 0 + 2 posicoes = v[5]
    printf("%d\n", *valores + 3); //soma 3 ao primeiro elemento
    return 0;
}