#include<stdio.h>

//countdownup recursivo
void countDownUp(int num){
    if (num == 1) printf("%d\n", num);
    else{
        printf("%d\n", num);
        countDownUp(num-1);
        printf("%d\n", num);
    }
}

//funcao principal
int main(){
    int num;
    printf("Digite um numero: ");
    scanf("%d", &num);
    countDownUp(num);
    return 0;
}