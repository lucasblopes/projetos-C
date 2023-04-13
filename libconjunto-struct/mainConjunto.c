//programa principal

#include <stdio.h>
#include <stdlib.h>
#include "libConjunto.h"


int main(){
    struct conjunto conjuntoA, conjuntoB, conjuntoAleatorio, conjuntoUniao, conjuntoInter, *conjuntoEscolhido, *conjunto1, *conjunto2;
    int cmd;

    //tamanho dos conjuntos inicia em 0
    zerarConjunto(conjuntoA);
    zerarConjunto(conjuntoB);
    zerarConjunto(conjuntoAleatorio);
    zerarConjunto(conjuntoUniao);
    zerarConjunto(conjuntoInter);

    printf("-BEM VINDO AO PROGRAMA DE CONJUNTOS INTEIROS\n");
    do {
        printf("-COMANDOS\n");
        printf("[1] Preencher um conjunto com elementos inteiros positivos.\n");
        printf("[2] Criar um conjunto com tamanho e elementos aleatorios.\n");
        printf("[3] Verificar se um conjunto eh vazio\n");
        printf("[4] Checar o tamanho de um conjunto.\n");
        printf("[5] Imprimir um conjunto.\n");
        printf("[6] Realizar a Uniao entre dois conjuntos.\n");
        printf("[7] Realizar a Interseccao de dois conjuntos.\n");
        printf("[0] Sair.\n");
        scanf("%d", &cmd);
        switch (cmd){

        //preencher conjunto A ou B
        case 1:
           printf("Selecione o conjunto que deseja preencher:\n");

            do {
                printf("[1] A\n");
                printf("[2] B\n");
                scanf("%d", &cmd);
                if (cmd != 1 && cmd != 2) printf("-Conjunto invalido!\n");
            } while (cmd != 1 && cmd != 2);

            switch (cmd){
                    case 1: 
                        preencherConjunto(conjuntoA);
                        printf("-Conjunto A preenchido com sucesso!\n");
                    break;
                    case 2: 
                        preencherConjunto(conjuntoB);
                        printf("-Conjunto B preenchido com sucesso!\n");
                    break;
            }    
        break;

        //criar conjunto aleatorio
        case 2:
            criarConjuntoAleatorio(conjuntoAleatorio);
            printf("-Conjunto aleatorio (C) criado com sucesso!.\n");

        break;

        //verificar se um conjunto eh vazio
        case 3:
            printf("Selecione o conjunto que deseja verificar se eh vazio:\n");
            selecionarConjunto(&conjuntoEscolhido, conjuntoA, conjuntoB, conjuntoAleatorio, conjuntoUniao, conjuntoInter);

            ehVazio(conjuntoEscolhido);
        break;
        
        //checar o tamanho de um conjunto
        case 4:
                printf("Selecione o conjunto que deseja checar o tamanho:\n");
                selecionarConjunto(&conjuntoEscolhido, conjuntoA, conjuntoB, conjuntoAleatorio, conjuntoUniao, conjuntoInter);
                printf("Conjunto Escolhido possui %d elementos.\n", (*conjuntoEscolhido).tam);
        break;

        //imprimir um conjunto
        case 5:
            printf("Selecione o conjunto que deseja imprimir:\n");
            selecionarConjunto(&conjuntoEscolhido, conjuntoA, conjuntoB, conjuntoAleatorio, conjuntoUniao, conjuntoInter);
            imprimirConjunto(conjuntoEscolhido);
        break;

        //uniao de dois conjuntos
        case 6:
            printf("Selecione o primeiro conjunto para realizar a uniao:\n");
            selecionarConjunto(&conjuntoEscolhido, conjuntoA, conjuntoB, conjuntoAleatorio, conjuntoUniao, conjuntoInter);
            conjunto1 = conjuntoEscolhido;

            printf("Selecione o segundo conjunto para realizar a uniao:\n");
            selecionarConjunto(&conjuntoEscolhido, conjuntoA, conjuntoB, conjuntoAleatorio, conjuntoUniao, conjuntoInter);
            conjunto2 = conjuntoEscolhido;

            uniao(conjunto1, conjunto2, conjuntoUniao);
            printf("-Conjunto Uniao formado com sucesso!\n");
        break;

        //realizar a interseccao entre dois conjuntos
        case 7:
            printf("Selecione o primeiro conjunto para realizar a interseccao:\n");
            selecionarConjunto(&conjuntoEscolhido, conjuntoA, conjuntoB, conjuntoAleatorio, conjuntoUniao, conjuntoInter);
            conjunto1 = conjuntoEscolhido;

            printf("Selecione o segundo conjunto para realizar a interseccao:\n");
            selecionarConjunto(&conjuntoEscolhido, conjuntoA, conjuntoB, conjuntoAleatorio, conjuntoUniao, conjuntoInter);
            conjunto2 = conjuntoEscolhido;

            //garante que o menor conjunto seja o primeiro parametro para a logica da interseccao funcionar
            if((*conjunto1).tam < (*conjunto2).tam)
                interseccao(conjunto1, conjunto2, conjuntoInter);
            else 
                interseccao(conjunto2, conjunto1, conjuntoInter);

            printf("-Conjunto Interseccao formado com sucesso!\n");
        break;

        //finalizar o programa
        case 0:
            printf("-Saindo...\n");

        break;

        default:
            printf("-Comando nao identificado.\n");
        }
    } while (cmd != 0);

    return 0;
}
