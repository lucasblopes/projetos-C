#include<stdio.h>

int main(){
    int a, b, maior;
    int *ptr_a, *ptr_b;

    printf("Digite o valor de a: \n");
    scanf("%d", &a);
    printf("Digite o valor de b: \n");
    scanf("%d", &b);   

    ptr_a = &a;
    ptr_b = &b;

    if(*ptr_a > *ptr_b) maior = *ptr_a;
    else maior = *ptr_b;

    printf("o maior valor digitado eh %d\n", maior); 
    return 0;
}