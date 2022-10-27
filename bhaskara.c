#include<stdio.h>
#include<math.h>

int main(){
    float a,b, c, x1, x2, delta;

    //le as constantes da equacao
    printf("a = ");
    scanf("%f", &a);
    printf("b = ");
    scanf("%f", &b);
    printf("c = ");
    scanf("%f", &c);

    //calula o delta e as raizes
    delta = (b*b - 4*a*c);
    x1 = (-b + sqrt(delta))/2;
    x2 = (-b - sqrt(delta))/2;

    //imprime o resultado
    if (delta < 0){
        printf("A equacao nao possui raizes reais.\n");
    }else {
        printf("x1: %.2f\n", x1);
        printf("x2: %.2f\n", x2);
    }

    return 0;
}