#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "libCalendario.h"

int main(){
    int op;
    char sai;
    Data data;
    Agenda *agenda;
    inicializarAgenda(&agenda);

    do {
        printf(" Digite uma opção:\n (0)\tcriar um único compromisso\n (1)\tadicionar compromissos na agenda\n (2)\tlistar os compromissos da agenda\n (3)\tremover um compromisso da agenda\n (4)\tsair!\n\n");
	    scanf("%d", &op);
        switch (op) {    
            case (0):{
                //criar um unico compromisso
                compromisso *c1 = criarCompromisso(&agenda);
                printf("\nVocê deseja adicionar esse compromisso na agenda [s/n] ?\n\n");
                sai = getchar();
                if (sai == 's' || sai == 'S'){
                    adicionarCompromisso(&agenda, c1);
                    printf("-Seu compromisso foi adicionado na agenda!\n");
                }
                else {
                    free(c1->data);
                    free(c1->horario);
                    free(c1->evento);
                    free(c1);
                }
                printf("\n");
            }
            break;
            case (1):{
                printf("\nCriando uma agenda de compromissos:\n\n");
                do {
                    compromisso *c2 = criarCompromisso(&agenda);
                    adicionarCompromisso(&agenda, c2);
                    printf("\n\nPressione 'x' para SAIR ou qualquer outra tecla para continuar...\n\n");
                    sai = getchar();
			    } while (sai != 'x');
                atualizarID(&agenda->inicio);
            }
            break;
            case(2):{
                if (agenda) {
                    printf("\n Agenda:\n\n");
                    atualizarID(&agenda->inicio);
                    listarCompromissos(&agenda);
                } else
                    printf("\n-A agenda está vazia!\n\n");
            }
            break;
            case(3):{
                removerCompromisso(&agenda);
                atualizarID(&agenda->inicio);
            }
            break;
            case(4):{
                destruirAgenda(&agenda);
                printf("-saindo...\n\n");
                exit(0);
            }
            break;
            default:
                printf("-comando invalido!\n");
        }
    } while (op != 4);

    return 0;
}
