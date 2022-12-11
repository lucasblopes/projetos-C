#include<stdio.h>

int main(){
    int a, b;
    int *ptr_a, *ptr_b;

    printf("Digite o valor de a: \n");
    scanf("%d", &a);
    printf("Digite o valor de b: \n");
    scanf("%d", &b);

    ptr_a = &a;
    ptr_b = &b;

    printf("%d + %d = %d\n", a, b, *ptr_a + *ptr_b);

    return 0;
}