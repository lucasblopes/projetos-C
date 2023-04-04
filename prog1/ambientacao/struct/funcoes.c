#include <stdio.h>

//definindo a struct ponto
struct ponto{
    int x;
    int y;
};

//definindo a struct retangulo
struct retangulo{
    struct ponto p1;
    struct ponto p2;
};

//funcao para criar um ponto
struct ponto criaPonto(int x, int y) {
    struct ponto tmp;

    tmp.x = x;
    tmp.y = y;

    return tmp;
};

//funcao para criar um retangulo
struct retangulo criaRetangulo(struct ponto p1, struct ponto p2){
    struct retangulo tmp;
    tmp.p1 = p1;
    tmp.p2 = p2;
    return tmp;
}

int main(){
    struct retangulo tela;
    struct ponto meio;

    tela = criaRetangulo(criaPonto(0,0), criaPonto(10,10));
    printf("Tela:\n\tp1 = (%d, %d),\n\tp2 = (%d, %d)\n",
    tela.p1.x, tela.p1.y, tela.p2.x, tela.p2.y);

    return 0;
    
};