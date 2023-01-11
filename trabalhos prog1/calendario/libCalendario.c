#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "libCalendario.h"

//inicia apontando para NULL
void inicializarAgenda(Agenda *agenda){
    agenda->inicio = NULL;
}

//imprime a agenda
void listarCompromissos(Agenda *agenda){
    compromisso *c = agenda->inicio;

    for(c = agenda->inicio; c != NULL; c = c->proximo)
        printf("-Evento %d: %s será na data %d/%d/%d, no horário [%d:%d-%d:%d].\n\n", c->id, c->evento, c->data->dia, c->data->mes, c->data->ano, c->horario->hora_inicial, c->horario->min_inicial, c->horario->hora_final, c->horario->min_final );
    printf("\n");
}

//verifica se o horario esta livre para o dia do compromisso
int horarioLivre(Agenda *agenda, compromisso *novo){
    compromisso *c;

    for(c = agenda->inicio; c != NULL; c = c->proximo){
        if (c->data->dia == novo->data->dia && c->data->mes == novo->data->mes && c->data->ano == novo->data->ano){
            //converte os horarios para min e compara
            int novo_Tinicial = (novo->horario->hora_inicial)*60 + novo->horario->min_inicial;
            int novo_Tfinal = (novo->horario->hora_final)*60 + novo->horario->min_final;
            int c_Tinicial = (c->horario->hora_inicial)*60 + c->horario->min_inicial;
            int c_Tfinal = (c->horario->hora_final)*60 + c->horario->min_final;
            if((novo_Tinicial >= c_Tinicial && novo_Tinicial < c_Tfinal) || (novo_Tfinal > c_Tinicial && novo_Tfinal <= c_Tfinal)){
                printf("\n[ERRO]-Horário indisponível!\n-Tente novamente\n\n");
                return 0;
            }
        }
    }
    printf("-Horário disponível!\n");

    return 1;
}

//retorna um unico compromisso
compromisso *criarCompromisso(Agenda *agenda){
    size_t tam = 1; 
    int tamstr, erro, disponibilidade;

    do {
        compromisso *c;
            c = malloc(sizeof(compromisso));
            c->data = malloc(sizeof(Data));
            c->horario = malloc(sizeof(Horario));
            c->evento = NULL;
        do {
            printf("Digite a data do compromisso [DD MM YYYY]: ");
            scanf("%d %d %d", &c->data->dia, &c->data->mes, &c->data->ano);
            if(c->data->dia < 1 || c->data->dia > 31 || c->data->mes < 1 || c->data->mes > 12 || c->data->ano < 1){
                printf("-[ERRO] Data inválida!\n");
                erro = 1;
            } else {
                erro = 0;
            }
        } while (erro == 1);

        do {
            printf("Digite o horário do início do compromisso [HH MM]: ");    
            scanf("%d %d", &c->horario->hora_inicial, &c->horario->min_inicial);
            if (c->horario->hora_inicial < 0 || c->horario->hora_inicial > 23 || c->horario->min_inicial < 0 || c->horario->min_inicial > 59){
                printf("-[ERRO] Horário inválido!\n");
                erro = 1;
            } else {
                erro = 0;
            }
        } while (erro == 1);

        do {
            printf("Digite a duração do seu compromisso [HH MM]: ");
            scanf("%d %d", &c->horario->hora_final, &c->horario->min_final);
            c->horario->hora_final += c->horario->hora_inicial;
            c->horario->min_final += c->horario->min_inicial;
            if(c->horario->min_final > 59){
                c->horario->min_final -= 60;
                c->horario->hora_final += 1 ;
            }
            if (c->horario->hora_final < 0 || c->horario->hora_final > 23 || c->horario->min_final < 0 || c->horario->min_final > 59 || c->horario->hora_final < c->horario->hora_inicial){
                printf("-[ERRO] Horário inválido!\n");
                erro = 1;
            } else {
                erro = 0;
            }
        } while (erro == 1);

        disponibilidade = horarioLivre(agenda, c);
        if (disponibilidade == 1) {
            getchar();

            printf("Digite o título do compromisso: ");
            tamstr = getline(&(c->evento), &tam, stdin);
            c->evento[strcspn(c->evento, "\n")] = '\0';

            printf("\n-Seu compromisso %s será na data %d/%d/%d, no horário [%d:%d-%d:%d].\n", c->evento, c->data->dia, c->data->mes, c->data->ano, c->horario->hora_inicial, c->horario->min_inicial, c->horario->hora_final, c->horario->min_final );

            return c;
        };
        free(c->data);
        free(c->horario);
        free(c->evento);
        free(c);
    } while (disponibilidade == 0);
}

//inserção ordenada de lista ligada
void adicionarCompromisso(Agenda *agenda, compromisso *novo) {
    compromisso *aux;

    //se a agenda estiver vazia, inicio aponta para o novo compromisso  
    if(agenda->inicio == NULL){
        novo->proximo = NULL;
        agenda->inicio = novo;
    }//verifica se o novo eh anterior ao primeiro compromisso
    else if (ehDepois(agenda->inicio, novo) == 1){
        novo->proximo = agenda->inicio;
        agenda->inicio = novo;
    }
    else {
        aux = agenda->inicio;
        while(aux->proximo && ehDepois(novo, aux->proximo) == 1){
            aux = aux->proximo;
        }
        novo->proximo = aux->proximo;
        aux->proximo = novo;
    }
}

//retorna 1 se c1 for depois de c2 e 0 c.c
int ehDepois(compromisso *c1, compromisso *c2){
    if (c1->data->ano > c2->data->ano)
        return 1;
    else if(c1->data->ano < c2->data->ano) return 0;

    if (c1->data->mes > c2->data->mes)
        return 1;
    else if(c1->data->mes < c2->data->mes) return 0;

    if (c1->data->dia > c2->data->dia)
        return 1;
    else if(c1->data->dia < c2->data->dia) return 0;

    if (c1->horario->hora_inicial > c2->horario->hora_inicial)
        return 1;
    if((c1->horario->hora_inicial == c2->horario->hora_inicial) && (c1->horario->min_inicial > c2->horario->min_inicial)) return 1;

    return 0;
}

//adiciona id aos compromissos da agenda
void atualizarID(compromisso *c) {
    int i = 1;
    while(c != NULL){
        c->id = i;
        i++;
        c = c->proximo;
    };
}

//libera memoria de um compromisso escolhido pelo id
void removerCompromisso(Agenda *agenda){
    compromisso *destruir = NULL;
    if (agenda->inicio == NULL)
        printf("\n-Não há compromissos na agenda!\n\n");
    else {
        compromisso *aux;
        int id;
        printf("-Digite o id do compromisso que deseja remover: ");
        scanf("%d", &id);
        if (agenda->inicio->id == id){
            destruir = agenda->inicio;
            agenda->inicio = destruir->proximo;
        }
        else{
            aux = agenda->inicio;
            while(aux->proximo && aux->proximo->id != id)
                aux = aux->proximo;
            if (aux->proximo){
                destruir = aux->proximo;
                aux->proximo = destruir->proximo;
            }
        }
        if (destruir) {
            free(destruir->data);
            free(destruir->horario);
            free(destruir->evento);
            free(destruir);
            printf("\n-Compromisso (%d) foi removido da lista!\n\n", id);
        }
        else
            printf("\n-Não existe um compromisso com o id %d!\n\n", id);
    }
}

//libera memoria de todos os compromisso da agenda
void destruirAgenda(Agenda *agenda){
    compromisso *p = NULL, *c = agenda->inicio;
    while(c){
        p = c->proximo;
        free(c->data);
        free(c->horario);
        free(c->evento);
        free(c);
        c = p;
    }
    printf("-agenda destruída!\n-memória liberada\n");
}