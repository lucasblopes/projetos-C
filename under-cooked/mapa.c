#include <ncurses.h>
#include <stdlib.h>
#include "mapa.h"
#include "tipos.h"

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

//retorna uma matriz
char** novaMatriz(int linhas, int colunas){

    char** matriz = malloc(linhas * sizeof *matriz);
        if(!matriz) {
            printw("memoria indisponivel\n");
            exit(1);
        }

    for(int i = 0; i < linhas; i++) 
        if((matriz[i] = malloc(colunas)) == NULL) {
            printw("memoria indisponivel\n");
            exit(1);
        }
    
    return matriz;
}

//retorna o mapa do jogo
struct Mapa* iniciarMapa() {

    struct Mapa* mapa = novoMapa();

    FILE* file = fopen("map.txt", "r"); 
        if(!file){
            printw("memoria indisponivel\n");
            exit(1);
        }
    fscanf(file, "tam = %d x %d", &mapa->colunas, &mapa->linhas);
    fgetc(file);

    char** matriz = novaMatriz(mapa->linhas, mapa->colunas);

    for(int i = 0; i < mapa->linhas; i++) {
        fgets(matriz[i], mapa->colunas, file);
        fgetc(file);
    }
    mapa->matriz = matriz;

    fclose(file);

    return mapa;
}

void imprimirMapa(struct Mapa* mapa) {
    
    for(int i = 0; i < mapa->linhas; i++) {
        for(int j = 0; j < mapa->colunas; j++)
            printw("%c", mapa->matriz[i][j]);
        printw("\n");
    }
    printw("\n");
}

//libera a memoria alocada para o mapa
struct Mapa* destruirMapa(struct Mapa* mapa) {

    if(!mapa) return NULL;

    for(int i = 0; i < mapa->linhas; i++)
        free(mapa->matriz[i]);
        
    free(mapa->matriz);
    free(mapa);
    return NULL;
}
