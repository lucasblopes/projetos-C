#include<stdio.h>
int num;

//contdown utilizando recursao
int countdown(int num){
    if (num == 1) printf("%d\n", num); //caso base
    else {
        printf("%d\n", num);
        countdown(num-1);
    }
    return 0;
}

//funcao principal
int main(){ 
    printf("Digite um numero: ");
    scanf("%d", &num);
    countdown(num);
    return 0;
}