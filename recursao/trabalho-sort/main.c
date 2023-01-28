#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ordenacao.h"

int main(){
	char nome[MAX_CHAR_NOME];
	int idxBusca;
	int numComp;

	//Dica: somente é posśivel criar vetores grandes utilizando alocação dinâmica de memória
	//Veja um exemplo de alocação dinâmica a seguir
	int tamVetor = 3;
	int* vetor = malloc(tamVetor * sizeof(int));
	if(vetor == NULL){
		printf("Falha fatal. Impossível alocar memoria.");
		return 1;
	}
	//Depois de alocado, o vetor pode ser utilizado normalmente
	//Não esqueça de desalocar no final do programa via free
		
	vetor[0] = 1;
	vetor[1] = 10;
	vetor[2] = 12;

	getNome(nome);
	printf("Trabalho de %s\n", nome);
	printf("GRR %u\n", getGRR());

	//Para medir o tempo, inclua time.h, e siga o exemplo:
	clock_t start, end;//variáveis do tipo clock_t
    double total;

	start = clock();//start recebe o "ciclo" corrente
	numComp = insertionSort(vetor, 3);
	end = clock();//end recebe o "ciclo" corrente
	//o tempo total é a diferença dividia pelos ciclos por segundo
	total = ((double)end - start)/CLOCKS_PER_SEC;
	printf("Tempo total: %f", total);

	numComp = selectionSort(vetor, 3);
	numComp = mergeSort(vetor, 3);
	numComp = quickSort(vetor, 3);
	numComp = heapSort(vetor, 3);

	for(int i=0; i < 3; i++){
		printf("%d ", vetor[i]);
	}
	idxBusca = buscaSequencial(vetor, 3, 10, &numComp);
	idxBusca = buscaBinaria(vetor, 3, 10, &numComp);

	printf("\n%d %d", idxBusca, numComp);
	printf("\n");

	//É obrigatório que você libere a memória alocada dinamicamente via free
	free(vetor);

	return 0;
}
