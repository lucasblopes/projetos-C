#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#define TAM 24

struct compromisso {
	int id;
	char *evento;
};

struct compromisso *criaCompromisso() {
	size_t tam = 1; 
	int tamstr;

	struct compromisso *c;
       	c = malloc(sizeof(struct compromisso));

	c->evento = malloc(tam * sizeof(char));

	/* falta algo aqui, não? ;-) */
	printf("Digite a data de seu compromisso:\n");
	scanf("%d", &c->id);
	getchar();

	printf("Digite o compromisso:\n");
	tamstr = getline(&(c->evento), &tam, stdin);
	c->evento[strcspn(c->evento, "\n")] = '\0';

	printf("Seu compromisso '%s' (%d) será marcado na data %d...\n", c->evento, tamstr-1, c->id);
	
	return c;

}

void adicionaCompromisso(struct compromisso **dia, struct compromisso *c) {
	c = criaCompromisso();

	/* falta algo aqui, não? ;-) */
	if (dia[c->id]) {
		printf("Hora %d já ocupada!\n", c->id);
		free(c->evento);
		free(c);
	} else {
		printf("Hora livre, preenchendo...\n");
		dia[c->id] = c;
	}
}

int main() {
	int op;

	printf("Digite uma opção:\n\t0\tcriar um único compromisso\n\t1\tcriar uma agenda para o dia\n\t2\tsair!\n\n");
	scanf("%d", &op);

	switch(op) {
		case (0): {
			/* suponha que você quer criar um único compromisso */
			struct compromisso *c1;
			c1 = criaCompromisso();
			printf("Evento: %s será no dia %d\n", c1->evento, c1->id);
		}
		break;
		case (1): {
			/* suponha uma agenda que representa um dia com 24 horas e 
			 * cada compromisso pode ser alocado dentro de uma hora... */
			struct compromisso *c2;
			struct compromisso *dia1[TAM];
			char sai;

			/* inicializa cada ponteiro com nulo */
			for (int i = 0; i < TAM; i++) {
				dia1[i] = NULL;
			}
	
			do {
				adicionaCompromisso(dia1, c2);
				printf("\n\nPressione 'x' para SAIR ou qualquer outra tecla para continuar...\n\n");
				sai = getchar();
			} while (sai != 'x');

			for (int j = 0; j < TAM; j++) {
				if (dia1[j]) {
				printf("Hora %d\t - %s\n", dia1[j]->id, dia1[j]->evento);
				}
			}
		} // fim do case
		break;
		case (2):
			exit(0);
	} // fim do switch

	return 0;
}
		