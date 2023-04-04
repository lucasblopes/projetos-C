//definindo um ponto no plano cartesiano com struct
#include <stdio.h>

int main(){
    //declaracao do tipo ponto (forma da struct)
    struct ponto {
        int x;
        int y;
    };

    //structs aninhadas
    struct retangulo {
        struct ponto p1;
        struct ponto p2;
    };

    //declaracao das variaveis tipo da struct (ponto)

    /*
    Outra forma de declaracao:
        struct {int x; int y;} p1, p2;
    OBS: p1 e p2 sao variaveis do tipo struct {int x; int y};
    */

    //atribuindo valores aos pontos
    struct ponto p1 = {0,0};
    struct ponto p2 = {1,2};
    struct ponto p3 = {3,5};

    //acessando os atributos dos pontos
    printf("O ponto p1 possui a seguinte coordenada: p1(%d, %d)\n", p1.x, p2.y);
    printf("O ponto p2 possui a seguinte coordenada: p2(%d, %d)\n", p2.x, p2.y);
    printf("O ponto p3 possui a seguinte coordenada: p3(%d, %d)\n", p3.x, p3.y);

    struct retangulo tela;

    tela.p1.x = 4;
    tela.p1.y = 3;
    tela.p2.x = 0;
    tela.p2.y = 0;

    //ou:
    //struct retangulo tela = {{4,3}, {0,0}};
    printf("Coordenadas dos pontos da tela:\np1(%d, %d)\np2(%d,%d)\n", tela.p1.x, tela.p1.y, tela.p2.x, tela.p2.y);


    return 0;
}