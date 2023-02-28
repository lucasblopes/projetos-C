#ifndef GAME_H
#define GAME_H

struct Game* iniciarGame();

void iniciarContagem(struct Game* game);

void gameLoop(struct Game* game);

void proximaFase(struct Game* game);

void imprimirGame(struct Game* game);

struct Game* liberarMemoria(struct Game* game);

#endif /* GAME_H */