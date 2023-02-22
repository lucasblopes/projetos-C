#ifndef MAP_H
#define MAP_H

struct Mapa* iniciarMapa();

struct Mapa* destruirMapa(struct Mapa* mapa);

void imprimirMapa(struct Mapa* mapa);

#endif /* MAP_H */