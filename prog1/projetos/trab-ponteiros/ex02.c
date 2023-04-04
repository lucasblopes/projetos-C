#include<stdio.h>

int somar(int *a, int *b){
    int soma = *a + *b;
    return soma;
}

int main(){
    int a, b;

    printf("Digite o valor de a: \n");
    scanf("%d", &a);
    printf("Digite o valor de b: \n");
    scanf("%d", &b);
    printf("%d + %d = %d\n", a, b, somar(&a,&b));

    return 0;
}