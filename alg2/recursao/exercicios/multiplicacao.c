#include<stdio.h>

int multiplicar(int n1, int n2){
    if (n2 == 0) return 0;
    return n1 + multiplicar(n1, n2-1);
}

int main(){
    int n1, n2, resultado;
    printf("Digite 2 numeros para multiplicar: \n");
    scanf("%d\n", &n1);
    scanf("%d", &n2);
    resultado = multiplicar(n1,n2);
    printf("%d x %d = %d\n", n1, n2, resultado);
    return 0;
}