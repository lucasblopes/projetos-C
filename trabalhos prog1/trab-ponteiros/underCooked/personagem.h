#ifndef PERSONAGEM_H
#define PERSONAGEM_H

struct Personagem* novoPersonagem();

void moverPersonagem(struct Personagem* boneco, struct Mapa* mapa, size_t x, size_t y);

void imprimirFase(int fase);

void imprimirVidas(int vidas);

void imprimirPontuacao(int pontos);

int colisao(struct Game* game, size_t x, size_t y);

struct Personagem* destruirPersonagem(struct Personagem* boneco);

#endif /* PERSONAGEM_H */