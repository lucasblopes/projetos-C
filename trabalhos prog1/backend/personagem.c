#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include "game.h"
#include "receitas.h"
#include "pedidos.h"
#include "tipos.h"

char novaSkin(){

    char skin;
    printf("Digite um caractere para definir a sua skin:\n");
    skin = getch();

    printf("%c\n", skin);

    printf("Digite uma tecla para continuar\n");
    getch();

    return skin;
}

//retorna uma struct personagem*
struct Personagem* novoPersonagem(struct Game* game){
     
    struct Personagem* boneco = malloc(sizeof *boneco);
        if(!boneco){
            printf("Erro de alocação de memória em novoPersonagem()\n");
            exit(1);
        }

    //coordenadas de spawn
    boneco->y = 3;
    boneco->x = 15;
    boneco->fase = 1;
    boneco->pontos = 0;
    boneco->vidas = 6;
    boneco->receita = novaReceita();
    boneco->skin = novaSkin();

    game->mapa->matriz[boneco->y][boneco->x] = boneco->skin;

    return boneco;
}

void imprimirFase(int fase){
    printf("[FASE %d]\n", fase);
}

void imprimirVidas(int vidas){
    printf("[Vidas: %d]\n", vidas);
}

void imprimirPontuacao(int pontos){
    printf("[Pontuacao: %d]\n", pontos);
}

//1 : colidiu; 0: nao colidiu
int colisao(struct Game* game, size_t x, size_t y){
    
    char proxPosicao = game->mapa->matriz[y][x];

    switch (proxPosicao){
        case 'R':
            push(game->boneco->receita, 'R');
            return 1;
        case 'F':
            push(game->boneco->receita, 'F');
            return 1;
        case 'p':
            push(game->boneco->receita, 'p');
            return 1;
        case 'H':
            push(game->boneco->receita, 'H');
            return 1;
        case 'Q':
            push(game->boneco->receita, 'Q');
            return 1;
        case 'S':
            push(game->boneco->receita, 'S');
            return 1;
        case 'P':
            push(game->boneco->receita, 'P');
            return 1;
        case 'o':
            destruirReceita(game->boneco->receita);
            game->boneco->receita = novaReceita();

            game->boneco->pontos -= 1;
            game->boneco->vidas -= 1;
            animacaoInteracao(game, y, x);
            return 1;
        case '@':
            game->boneco->pontos += validarReceita(game->boneco->receita, game->pedidos->cabeca->refID, game->cardapio);    
            if(validarReceita(game->boneco->receita, game->pedidos->cabeca->refID, game->cardapio) > 0){
                pop(game->pedidos);
                //game->clientes -= 1;
            }
            else 
                game->boneco->vidas -= 2;

            destruirReceita(game->boneco->receita);
            game->boneco->receita = novaReceita();

            //se nao tem mais pedidos vai para outra fase
            if(!game->pedidos->cabeca)
                proximaFase(game);
            animacaoInteracao(game, y, x);
            return 1;
        case '[':
            return 1;
        case ']':
            return 1;
        case '|':
            return 1;
        case '-':
            return 1;
    }

    return 0;
}

void moverPersonagem(struct Personagem* boneco, struct Mapa* mapa, size_t x, size_t y){
    
    mapa->matriz[boneco->y][boneco->x] = ' ';
    mapa->matriz[y][x] = boneco->skin;
    boneco->x = x;
    boneco->y = y;
}

struct Personagem* destruirPersonagem(struct Personagem* boneco){

    if(!boneco) return NULL;
    
    destruirReceita(boneco->receita);
    free(boneco);
    return NULL;
}

