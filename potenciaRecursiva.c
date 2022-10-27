#include<stdio.h>
#include<math.h>

//calcula a^b recursivamente
int pot(int a, int b){
    if (b == 0) return 1;
    if (b % 2 == 0) return pot(a*a, floor(b/2));
    return pot(a*a, floor(b/2))*a;
}

//funcao principal
int main(){
    int a,b;
    printf("a = ");
    scanf("%d", &a);
    printf("b = ");
    scanf("%d", &b);
    printf("a ^ b = ");
    printf("%d\n", pot(a,b));
}