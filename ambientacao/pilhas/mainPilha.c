#include<stdio.h>
#include<stdlib.h>
#include "libPilha.h"


int main(){
    int op, num;
    Pilha *pilha = newStack();
    if (pilha == NULL)
        printf("erro de alocação de memória!\n");

    do {    
        printf("\nOperações:\n0: inserir elemento\n1: remover elemento\n2: Imprimir elementos\n3: Destruir pilha\n4: Sair\n\n");
        scanf("%d", &op);
        switch(op){
            case 0:
                printf("Digite o valor que deseja inserir na pilha: ");
                scanf("%d", &num);
                push(pilha, num);
            break;

        case 1: {
                Nodo *remover = malloc(sizeof(*remover));
                remover = pop(pilha);
                printf("%d removido com sucesso!\n", remover->dado);
                free(remover);
            break;
        }
            case 2:
                show(pilha);
                break;
            case 3:
                destruir(pilha);
            break;
            case 4:
                printf("saindo...\n");
                destruir(pilha);
                free(pilha);
        }
    } while (op != 4);
    return 0;
}