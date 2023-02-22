#include <stdlib.h>
#include <time.h>
#include "menus.h"
#include "game.h"

int main(){

    struct Game* game = iniciarGame();
    iniciarContagem(game);
    gameLoop(game);

    char cmd = 0;
    do {
        cmd = getch();
    } while (cmd != 'q' && cmd != 'Q');
    game = liberarMemoria(game);

    endwin();
    return 0;
}