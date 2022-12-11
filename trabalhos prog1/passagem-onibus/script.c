#include<stdio.h>

#define FILEIRA 12
#define POLTRONA 4

//preenche o vetor onibus com 'x' nas poltronas invalidas e '0' nas outras
void preencherVetor(char onibus[FILEIRA][POLTRONA]){
    for(int i = 0; i < FILEIRA; i++)
            for(int j = 0; j < POLTRONA; j++) 
                onibus[i][j] = '0';
}

//imprime o vetor do onibus
void imprimirVetor(char onibus[FILEIRA][POLTRONA]){
    printf("     [1][2][3][4]\n");
    printf("[ 1]  x\n");
    for(int i = 0; i < FILEIRA; i++){
        printf("[%2d] ", i+2);
        for(int j = 0; j < POLTRONA; j++) printf(" %c ", onibus[i][j]);
        printf("\n");
    }
    printf("[14]           x");
}

//verifica se o assento escolhido pelo usuario esta disponivel e retorna o numero do lugar nesse caso
int verificarAssento(char onibus[FILEIRA][POLTRONA], int assento){
    int disponibilidade = 1; // 0 se for indisponivel
    int num = 0; //numero dos assentos

    assento--;
    if(assento == 0){
        printf("\n--ERRO! esse eh o assento do motorista!\n");
        disponibilidade = 0;
    }
    else if(assento == 49){
        printf("\n--ERRO! voce selecionou a posicao do banheiro\n");
        disponibilidade = 0;
    }
    else if(assento < 0 || assento > 49) printf("\n--ERRO! esse assento nao esta disponivel\n");

    for(int i = 0; i < FILEIRA; i++){
        for(int j = 0; j < POLTRONA; j++){
            num++;
            if(num == assento){
                if(onibus[i][j] == 'x') {
                    printf("\n--Poltrona ocupada!\n");
                    disponibilidade = 0;
                }
                else {
                    printf("\n--Poltrona Livre!\n");
                    disponibilidade += assento;
                }
            }
        }
    }
    return disponibilidade;
}

//reserva o assento escolhido pelo usuario, considerando que ele esteja disponivel
int reservarAssento(char onibus[FILEIRA][POLTRONA], int assento){
    int reservado, num = 0; //0 se nao foi reservado e 1 caso contrario
    assento--;
    for(int i = 0; i < FILEIRA; i++){
        for(int j = 0; j < POLTRONA; j++){
            num++;
            if (num == assento) {
                onibus[i][j] = 'x';
                reservado = 1;
            }
        }
    }
    return reservado;
}

int main(){
    char onibus[FILEIRA][POLTRONA];
    int assento, comando;

    preencherVetor(onibus);
    do {  
        printf("\n======================\n");
        printf("  RESERVE UM ASSENTO\n");
        printf("======================\n");
        printf("Comandos: \n");
        printf("[1] : Verificar se um assento esta disponivel.\n");
        printf("[2] : Reservar um assento.\n");
        printf("[3] : Imprimir o mapa  de assentos do onibus. \n");
        printf("[0] : Sair.\n");
        printf("Digite um comando: ");
        scanf("%d", &comando);
        switch (comando){
            case 1:
                printf("\n--Qual assento voce deseja verificar? [1-50]: ");
                scanf("%d", &assento);
                verificarAssento(onibus, assento);
                break;
            case 2: 
                printf("\n--Qual assento voce deseja reservar? [1-50]: ");
                scanf("%d", &assento);
                if(verificarAssento(onibus, assento) != 0){
                    reservarAssento(onibus, assento);
                    printf("\n--Assento %d reservado com sucesso!\n", assento);
                } else printf("\n--ERRO! Assento indisponível!\n");
                break;
            case 3: 
                printf("\nMapa das poltronas do onibus:\n");
                imprimirVetor(onibus);
                break;
            case 0:
                printf("=================\n");
                printf("  BOA VIAGEM\n");
                printf("=================\n");
                break;
            default:
                printf("\n--Comando inválido! Digite novamente: ");
                scanf("%d", &comando);
                break;
        }
    } while (comando != 0);

    return 0;
}