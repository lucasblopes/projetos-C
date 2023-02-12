#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include <time.h>
#include "game.h"
#include "tipos.h"
#include "pedidos.h"
#include "receitas.h"
#include "personagem.h"
#include "mapa.h"

//númeo de pedidos por fase
#define CLIENTES 5
//coordenadas de spawn do jogador
#define Y 3
#define X 15

void iniciarContagem(struct Game* game){

    game->mapa->matriz[Y][X] = '3';
    imprimirGame(game);
    usleep(800000);
    game->mapa->matriz[Y][X] = '2';
    imprimirGame(game);
    usleep(800000);
    game->mapa->matriz[Y][X] = '1';
    imprimirGame(game);
    usleep(800000);
    game->mapa->matriz[Y][X] = '0';
    imprimirGame(game);
    usleep(800000);
    game->mapa->matriz[Y][X] = game->boneco->skin;
}

struct Game* iniciarGame(){

    srand((unsigned)time(NULL)); //cria seed aleatória
    struct Game* game = malloc(sizeof *game);
        if(!game){
            printw("Erro de alocação de memória em iniciarGame()!\n");
            exit(1);
        }
  
    game->clientes = CLIENTES;
    game->cardapio = novoCardapio();
    game->pedidos = criarLista();
    game->mapa = iniciarMapa();
    game->boneco = novoPersonagem(game);
    gerarPedidos(game->pedidos, game->clientes);
    return game;
}

struct Game* liberarMemoria(struct Game* game){

    game->boneco = destruirPersonagem(game->boneco);
    game->mapa = destruirMapa(game->mapa);
    game->cardapio = destruirCardapio(game->cardapio);
    game->pedidos = destruirLista(game->pedidos);
    free(game);
    return NULL;
}

void imprimirGame(struct Game* game){

    erase();
    imprimirFase(game->boneco->fase);
    imprimirMapa(game->mapa);
    imprimirVidas(game->boneco->vidas);
    imprimirPontuacao(game->boneco->pontos);
    imprimirReceita(game->boneco->receita);
    imprimirPedidos(game->pedidos);
    refresh();
}

int interpretarTecla(struct Game* game){
    
    int tecla = 0;
    tecla = getch();

    switch (tecla){
        case 'w':
        case 'W':
        case KEY_UP:
            if(!colisao(game, game->boneco->x, game->boneco->y-1))
                moverPersonagem(game->boneco, game->mapa, game->boneco->x, game->boneco->y-1);
            break;
        case 'a':
        case 'A':
        case KEY_LEFT:
            if(!colisao(game, game->boneco->x-1, game->boneco->y))
                moverPersonagem(game->boneco, game->mapa, game->boneco->x-1, game->boneco->y);
            break;
        case 's':
        case 'S':
        case KEY_DOWN:
            if(!colisao(game, game->boneco->x, game->boneco->y+1))
                moverPersonagem(game->boneco, game->mapa, game->boneco->x, game->boneco->y+1);
            break;
        case 'd':
        case 'D':
        case KEY_RIGHT:
            if(!colisao(game, game->boneco->x+1, game->boneco->y))
                moverPersonagem(game->boneco, game->mapa, game->boneco->x+1, game->boneco->y);
            break;
        case 'q':
        case 'Q':
            return 1;
            break;
    }
    return 0;
}

void proximaFase(struct Game* game){

    game->boneco->fase += 1;
    game->boneco->pontos += 20; //ganha 20 pontos a cada fase
    game->clientes = CLIENTES;
    gerarPedidos(game->pedidos, game->clientes);
}

void gameLoop(struct Game* game){

    int quit = 0;
    imprimirGame(game);
    while(!quit && game->boneco->vidas > 0){
        quit = interpretarTecla(game);
        imprimirGame(game);
    }
}