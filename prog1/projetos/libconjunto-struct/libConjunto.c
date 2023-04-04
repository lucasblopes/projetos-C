//implementacoes
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "libConjunto.h"

//preenche um vetor com -1 para indicar que ele esta vazio
void zerarConjunto(struct conjunto v){
    v.tam = 0;
}

//usuario seleciona qual conjunto ira manipular
void selecionarConjunto(struct conjunto *p_conjuntoEscolhido, struct conjunto vA, struct conjunto vB, struct conjunto vC, struct conjunto vUniao, struct conjunto vInter){
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
void ehVazio(struct conjunto v){
    if (v.tam == 0) 
        printf("-Conjunto Vazio!\n");
    else
        printf("-Conjunto nao vazio!\n");
}

//leitura de dados e ordenacao do vetor A
void preencherConjunto(struct conjunto v){
    int num;

    do {
        printf("Qual o tamanho do conjunto? [0-100]\n");
        scanf("%d", &v.tam);
        if (v.tam < 0 || v.tam > 100) printf("-O tamanho precisa estar contido no intervalo [0-100]!\n");
    } while (v.tam < 0 || v.tam > 100);

    printf("Digite %d valores inteiros positivos:\n", v.tam);
    
    for(int i = 0; i < v.tam; i++){
        do {
            scanf("%d", &num);
            if(num < 0) printf("-O numero precisa ser inteiro positivo!\n");
        } while (num < 0);
        v.dado[i] = num;
    }
    
    ordenarConjunto(v);
}

//imprime o vetor
void imprimirConjunto(struct conjunto v){
    if (v.tam == 0) 
        printf("{ }\n");
    else{
        printf("{ ");
        for(int i = 0; i < v.tam; i++)
            printf("%d ", v.dado[i]);
        printf("}\n");
    }
}

//retorna o tamanho do conjunto com numeros aleatorios e ordena o vetor B
void criarConjuntoAleatorio(struct conjunto v){
    srand((unsigned)time(NULL));

    //tamanho varia de 0 ate 100 elementos
    for(int i = 0 ; i <= rand() % 100 ; i++){
        //elementos variam de 0 a 100
        v.dado[i] = rand() % 100;
        v.tam++;
    }

    ordenarConjunto(v);
}

//realiza a uniao dos dois conjuntos
void uniao(struct conjunto v1, struct conjunto v2, struct conjunto vUniao){
    int repetido;

    for(int i = 0; i < v1.tam + v2.tam; i++){
        repetido = 0;
        if (i < v1.tam) {
            //esse laco evita que seja alocado valores repetidos
            for(int j = 0; j < vUniao.tam; j++)
                if(v1.dado[i] == vUniao.dado[j]) 
                    repetido++;
            if(repetido == 0){
                vUniao.dado[vUniao.tam] = v1.dado[i];
                vUniao.tam++;
            }
        }
        else {
            for(int j = 0; j < vUniao.tam; j++)
                if(v2.dado[i-v1.tam] == vUniao.dado[j]) 
                    repetido++;
            if(repetido == 0){
                vUniao.dado[vUniao.tam] = v2.dado[i-v1.tam];
                vUniao.tam++;
            }      
        }  
    };

    ordenarConjunto(vUniao);
}

//realiza a interseccao dos conjuntos A e B
void interseccao(struct conjunto v1, struct conjunto v2, struct conjunto vInter){
    int encontrou;

    for(int i = 0; i < v1.tam; i++){
            encontrou = 0;
            for(int j = 0; v2.dado[j] <= v1.dado[i] && encontrou == 0; j++){
                if(v1.dado[i] == v2.dado[j]){ 
                    for(int k = 0; k < vInter.tam; k++)
                        if(v1.dado[i] == vInter.dado[k]) encontrou++;
                    if(encontrou == 0){
                        vInter.dado[vInter.tam] = v1.dado[i];
                        vInter.tam++;
                    }
                    encontrou++;
                }
            }
        }
}

//ordena o vetor pelo metodo de insersao
void ordenarConjunto(struct conjunto v){
    int i, j, aux;

    for(i = 1; i < v.tam; i++){
        aux = v.dado[i];
        for(j = i-1; j >= 0 && aux < v.dado[j]; j--)
            v.dado[j+1] = v.dado[j];
        v.dado[j+1] = aux;
    }
}