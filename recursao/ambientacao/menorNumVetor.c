#include<stdio.h>

#define MAX 1024

//entrada de dados em um vetor de tamanho n
void lerVetor(int n, int *v){
    printf("Digite %d valores: \n", n);
    for(int i = 0; i < n; i++) scanf("%d", &v[i]);
}

//imprime o vetor
void imprimirVetor(int a, int b, int *v){
    for(int i = a; i <= b; i++) printf("%d ", v[i]);
    printf("\n");
}

//recebe o vetor e retorna o seu menor elemento
int menorValor(int a, int b, int *v){
    int m;
    if(a == b) return a;
    m = menorValor(a, b-1, v);
    if(v[b] < v[m]) m = b;
    return m;
}

int main(){
    int a, b, n, v[MAX];
  
    do {
        printf("Digite o valor de n, sendo n o tamanho do vetor: (1 <= n <= 1024) ");
        scanf("%d", &n);
    } while (n < 1 || n > 1024);

    lerVetor(n, v);

    do{
        printf("Digite o intervalo [a,b] do vetor que deseja verificar: \n");
        printf("a = ");
        scanf("%d", &a);
        printf("b = ");
        scanf("%d", &b);
    }while (a < 0 || a > b || b > n-1);

    imprimirVetor(a, b, v);
    printf("Menor numero = %d\n", v[menorValor(a, b, v)]);

    return 0;
}