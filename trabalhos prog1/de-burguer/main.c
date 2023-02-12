#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
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

    struct Game* game = iniciarGame();
    iniciarContagem(game);
    gameLoop(game);
    //imprimirTelaFinal(game)
    game = liberarMemoria(game);

    char cmd;
    do {
        printw("Digite 'Q' para sair\n");
        cmd = getch();
    } while (cmd != 'q' && cmd != 'Q');

    endwin();
    return 0;
}