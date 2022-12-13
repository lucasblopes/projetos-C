#include <stdio.h>

void imprimirVetor(int v[]){
    for(int i = 0; i < 5; i++)
        printf("%d ", v[i]);
    printf("\n");
}

void selecionarVetor(int **p_vetorEscolhido, int *vA, int *vB){
    int cmd;
    printf("0 - A\n");
    printf("1 - B\n");
    scanf("%d", &cmd);
    
    if(cmd == 0) *p_vetorEscolhido = vA;
    else *p_vetorEscolhido = vB;
}

int main(){
    int vetorA[5] = {1,2,3,4,5},
        vetorB[5] = {6,7,8,9,10},
        *p_vetorEscolhido;

    printf("Escolha qual vetor deseja imprimir: [A/B]\n");
    selecionarVetor(&p_vetorEscolhido, vetorA, vetorB);
    imprimirVetor(p_vetorEscolhido);
    return 0;
}