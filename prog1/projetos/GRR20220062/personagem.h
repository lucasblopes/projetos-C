#ifndef PERSONAGEM_H
#define PERSONAGEM_H

struct Personagem* novoPersonagem();

void moverPersonagem(struct Personagem* boneco, struct Mapa* mapa, int x, int y);

void imprimirFase(int fase);

void imprimirVidas(int vidas);

void imprimirPontuacao(int pontos);

int colisao(struct Game* game, int x, int y);

struct Personagem* destruirPersonagem(struct Personagem* boneco);

#endif  