#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "game.h"
#include "tipos.h"
#include "pedidos.h"
#include "receitas.h"
#include "personagem.h"
#include "mapa.h"

//numero de pedidos por fase
#define CLIENTES 5
//coordenadas de spawn do jogador
#define Y 3
#define X 15

//contagem de 3 segundos antes de iniciar o game
void iniciarContagem(struct Game* game){

    game->mapa->matriz[Y][X] = '3';
    imprimirGame(game);
    sleep(1);
    game->mapa->matriz[Y][X] = '2';
    imprimirGame(game);
    sleep(1);
    game->mapa->matriz[Y][X] = '1';
    imprimirGame(game);
    sleep(1);
    game->mapa->matriz[Y][X] = '0';
    imprimirGame(game);
    sleep(1);
    game->mapa->matriz[Y][X] = game->boneco->skin;
}

//inicializa os mesmbros da struct game
struct Game* iniciarGame(){

    srand((unsigned)time(NULL)); //cria seed aleatória
    struct Game* game = malloc(sizeof *game);
        if(!game){
            printf("Erro de alocação de memória em iniciarGame()!\n");
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

//realiza free nos mallocs 
struct Game* liberarMemoria(struct Game* game){

    game->boneco = destruirPersonagem(game->boneco);
    game->mapa = destruirMapa(game->mapa);
    game->cardapio = destruirCardapio(game->cardapio);
    game->pedidos = destruirLista(game->pedidos);
    free(game);
    return NULL;
}

//imprime todas as informacoes na tela
void imprimirGame(struct Game* game){

    imprimirFase(game->boneco->fase);
    imprimirMapa(game->mapa);
    imprimirVidas(game->boneco->vidas);
    imprimirPontuacao(game->boneco->pontos);
    imprimirReceita(game->boneco->receita);
    imprimirPedidos(game->pedidos);
}

//realiza uma acao de acordo com a tecla digitada
int solicitarTecla(struct Game* game){
    
    int tecla = 0;
    tecla = getch();

    switch (tecla){
        case 'w':
        case 'W':
            if(!colisao(game, game->boneco->x, game->boneco->y-1))
                moverPersonagem(game->boneco, game->mapa, game->boneco->x, game->boneco->y-1);
            break;
        case 'a':
        case 'A':
            if(!colisao(game, game->boneco->x-1, game->boneco->y))
                moverPersonagem(game->boneco, game->mapa, game->boneco->x-1, game->boneco->y);
            break;
        case 's':
        case 'S':
            if(!colisao(game, game->boneco->x, game->boneco->y+1))
                moverPersonagem(game->boneco, game->mapa, game->boneco->x, game->boneco->y+1);
            break;
        case 'd':
        case 'D':
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

//atualiza o jogo para a proxima fase
void proximaFase(struct Game* game){

    game->boneco->fase += 1;
    game->boneco->pontos += 20; //ganha 20 pontos a cada fase
    game->clientes += 1;
    gerarPedidos(game->pedidos, game->clientes);
}

//solicita tecla e imprime as informacoes na tela enquanto estiver vivo
void gameLoop(struct Game* game){

    int quit = 0;
    imprimirGame(game);
    while(!quit && game->boneco->vidas > 0){
        quit = solicitarTecla(game);
        imprimirGame(game);
    }
}