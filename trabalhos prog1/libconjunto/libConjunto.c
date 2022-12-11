//implementacoes
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "libConjunto.h"

//preenche um vetor com -1 para indicar que ele esta vazio
void preencherMenosUm(int *v){
    for(int i = 0; i < 100; i++)
        v[i] = -1;
}

//usuario seleciona qual conjunto ira manipular
void selecionarConjunto(int **p_conjuntoEscolhido, int *vA, int *vB, int *vC, int *vUniao, int *vInter){
    int cmd;

    do {
        printf("[1] A\n");
        printf("[2] B\n");
        printf("[3] C (Aleatorio)\n");
        printf("[4] Uniao\n");
        printf("[5] Interseccao\n");
        scanf("%d", &cmd);
        if (cmd < 1 || cmd > 5) printf("-Conjunto invalido!\n");
    } while (cmd < 1 || cmd > 5);

    switch (cmd){
        case 1: *p_conjuntoEscolhido = vA;
        break;
        case 2: *p_conjuntoEscolhido = vB;
        break;
        case 3: *p_conjuntoEscolhido = vC;
        break;
        case 4: *p_conjuntoEscolhido = vUniao;
        break;
        case 5: *p_conjuntoEscolhido = vInter;
        break;
    }
}

//verifica se um conjunto eh vazio
void ehVazio(int *v){
    if (v[0] == -1) 
        printf("-Conjunto Vazio!\n");
    else
        printf("-Conjunto nao vazio!\n");
}

//retorna a quantidade de elementos do conjunto
int tamanho(int *v){
    for(int i = 0; i < 200; i++){
        if(v[i] == -1){
            if(i == 0) return 0;
            else return i;
        }
    }
    return 200;
}

//leitura de dados e ordenacao do vetor A
void preencherConjunto(int *v){
    int num, tam;

    do {
        printf("Qual o tamanho do conjunto? [0-100]\n");
        scanf("%d", &tam);
        if (tam < 0 || tam > 100) printf("-O tamanho precisa estar contido no intervalo [0-100]!\n");
    } while (tam < 0 || tam > 100);

    printf("Digite %d valores inteiros positivos:\n", tam);
    
    for(int i = 0; i < tam; i++){
        do {
            scanf("%d", &num);
            if(num < 0) printf("-O numero precisa ser inteiro positivo!\n");
        } while (num < 0);
        v[i] = num;
    }
    
    insertionSort(v);
}

//imprime o vetor
void imprimirConjunto(int *v){

    int tam = tamanho(v);

    if (v[0] == -1) 
        printf("{ }\n");
    else{
        printf("{ ");
        for(int i = 0; i < tam; i++)
            printf("%d ", v[i]);
        printf("}\n");
    }
}

//retorna o tamanho do conjunto com numeros aleatorios e ordena o vetor B
void criarConjuntoAleatorio(int *v){
    int tam = 0;
    srand((unsigned)time(NULL));

    //tamanho varia de 0 ate 100 elementos
    for(int i = 0 ; i <= rand() % 100 ; i++){
        //elementos variam de 0 a 100
        v[i] = rand() % 100;
        tam++;
    }

    insertionSort(v);
}

//realiza a uniao dos dois conjuntos
void uniao(int *v1, int *v2, int *vUniao){
    int tam1, tam2, tamUniao, repetido;

    tam1 = tamanho(v1);
    tam2 = tamanho(v2);
    tamUniao = 0;

    for(int i = 0; i < tam1 + tam2; i++){
        repetido = 0;
        if (i < tam1) {
            //esse laco evita que seja alocado valores repetidos
            for(int j = 0; j < tamUniao; j++)
                if(v1[i] == vUniao[j]) 
                    repetido++;
            if(repetido == 0){
                vUniao[tamUniao] = v1[i];
                tamUniao++;
            }
        }
        else {
            for(int j = 0; j < tamUniao; j++)
                if(v2[i-tam1] == vUniao[j]) 
                    repetido++;
            if(repetido == 0){
                vUniao[tamUniao] = v2[i-tam1];
                tamUniao++;
            }      
        }  
    };

    insertionSort(vUniao);
}

//realiza a interseccao dos conjuntos A e B
void interseccao(int *v1, int *v2, int *vInter){
    int tam1, tam2, encontrou, tamInter;

    tam1 = tamanho(v1);
    tam2 = tamanho(v2);
    tamInter = 0;

    for(int i = 0; i < tam1; i++){
            encontrou = 0;
            for(int j = 0; v2[j] <= v1[i] && encontrou == 0; j++){
                if(v1[i] == v2[j]){ 
                    for(int k = 0; k < tamInter; k++)
                        if(v1[i] == vInter[k]) encontrou++;
                    if(encontrou == 0){
                        vInter[tamInter] = v1[i];
                        tamInter++;
                    }
                    encontrou++;
                }
            }
        }
}

//ordena o vetor pelo metodo de insersao
void insertionSort(int *v){
    int i, j, aux, tam;
    
    tam = tamanho(v);

    for(i = 1; i < tam; i++){
        aux = v[i];
        for(j = i-1; j >= 0 && aux < v[j]; j--)
            v[j+1] = v[j];
        v[j+1] = aux;
    }
}