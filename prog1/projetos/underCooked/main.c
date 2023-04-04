#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include "menus.h"
#include "game.h"

//inicia o ncurses
void iniciarDisplay(){
    
    initscr();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);
}

int main(){

    iniciarDisplay();

    imprimirLogo();
    getch();

    imprimirInstrucoes();
    getch();
    erase();

    struct Game* game = iniciarGame();
    iniciarContagem(game);
    gameLoop(game);

    imprimirTelaFinal(game);
    char cmd = 0;
    do {
        cmd = getch();
    } while (cmd != 'q' && cmd != 'Q');
    game = liberarMemoria(game);

    endwin();
    return 0;
}