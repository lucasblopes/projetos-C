//exponenciacao
#include<stdio.h>

int exponencial(int x, int n){
    if (n == 0)
        return 1;
    return x*exponencial(x, n-1);
}

int main(){
    int x, n;

    printf("x = ");
    scanf("%d", &x);
    printf("n = ");
    scanf("%d", &n);
    printf("%d^%d = %d\n", x, n, exponencial(x, n));

    return 0;
}