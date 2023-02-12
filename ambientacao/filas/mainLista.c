#include "libLista.h"
#include <stdlib.h>
#include <stdio.h>

int main(){
    int op, num;
    struct lista* lista = criarLista();
    if (lista == NULL)
        printf("erro de alocação de memória!\n");

    do {    
        printf("\nOperações:\n0: inserir na cabeça\n1: inserir ordenado\n2: inserir na cauda\n3: buscar elemento\n4: imprimir lista\n5: remover elemento\n6: Destruir lista\n7: Sair\n\n");
        scanf("%d", &op);
        switch(op){
            case 0:{
                printf("Digite o valor que deseja inserir na cabeça da Lista: ");
                scanf("%d", &num);
                insereCabeca(lista, num);
            }break;
            case 1:{
                printf("Digite o valor que deseja inserir ordenado: ");
                scanf("%d", &num);
                insereOrdenado(lista, num);
            }break;
            case 2:{
                printf("Digite o valor que deseja inserir na cauda da Lista: ");
                scanf("%d", &num);
                insereCauda(lista, num);
            }break;
            case 3:{
                if(!lista->cabeca)
                    printf("A lista está vazia!\n");
                else {
                    printf("Digite o número que deseja buscar:");
                    scanf("%d", &num);

                    if(busca(lista, num) == -1) 
                        printf("%d não está presente na lista!\n", num);
                    else
                        printf("%d é o elemento número %d da fila\n", num, busca(lista,num));
                }
            }break;
            case 4:{
                show(lista);
            }break;
            case 5:{
                struct nodo *remover = pop(lista);
                if(remover)
                    printf("%d removido da lista!\n", remover->dado);
                free(remover);
            }break;
            case 6:{
                destruir(lista);
                printf("Fila destruída! Memória liberada!\n");
            }break;
            case 7:{
                printf("saindo...\nmemória destruída!\n");
                destruir(lista);
                free(lista);
            }break;
        }
    } while (op != 7);

    return 0;
}