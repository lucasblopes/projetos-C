#include <ncurses.h>
#include <stdlib.h>
#include "mapa.h"
#include "tipos.h"

//retorna o ponteiro para mapa.txt
FILE* abrirMapa(char* diretorio){

    FILE* file = fopen(diretorio, "r"); //read 
        if(!file){
            printw("memoria indisponivel\n");
            exit(1);
        }
    return file;
}

//retorna uma matriz
char** novaMatriz(size_t linhas, size_t colunas){

    char** matriz = malloc(linhas * sizeof *matriz);
        if(!matriz) {
            printw("memoria indisponivel\n");
            exit(1);
        }

    for(size_t i = 0; i < linhas; i++) 
        if((matriz[i] = malloc(colunas)) == NULL) {
            printw("memoria indisponivel\n");
            exit(1);
        }
    
    return matriz;
}

//retorna uma struct Mapa*
struct Mapa* novoMapa() {

    struct Mapa* mapa = malloc(sizeof *mapa);
        if(!mapa){
            printw("memoria indisponivel\n");
            exit(1);
        }
    
    mapa->matriz = NULL;
    mapa->colunas = 0;
    mapa->linhas = 0;

    return mapa;
}

//copia o conteudo de map.txt para a matriz
void lerMapa(struct Mapa* mapa, FILE* file){

    fscanf(file, "tam = %zu x %zu", &mapa->colunas, &mapa->linhas);
    fgetc(file);

    char** matriz = novaMatriz(mapa->linhas, mapa->colunas);

    for(size_t i = 0; i < mapa->linhas; i++) {
        fgets(matriz[i], mapa->colunas, file);
        fgetc(file);
    }
    mapa->matriz = matriz;
}

//retorna o mapa do jogo
struct Mapa* iniciarMapa() {

    struct Mapa* mapa = novoMapa();
    FILE* file = abrirMapa("map.txt");
    lerMapa(mapa, file);
    fclose(file);

    return mapa;
}

void imprimirMapa(struct Mapa* mapa) {
    
    for(size_t i = 0; i < mapa->linhas; i++) {
        for(size_t j = 0; j < mapa->colunas; j++)
            printw("%c", mapa->matriz[i][j]);
        printw("\n");
    }
    printw("\n");
}

//libera a memoria alocada para o mapa
struct Mapa* destruirMapa(struct Mapa* mapa) {

    if(!mapa) return NULL;

    for(size_t i = 0; i < mapa->linhas; i++)
        free(mapa->matriz[i]);
        
    free(mapa);
    return NULL;
}
