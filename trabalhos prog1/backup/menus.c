#include <ncurses.h>

#include "tipos.h"

void imprimirLogo(void){

    printw("                 _            _____            _            _ \n"           );
    printw("                | |          / ____|          | |          | |\n"           );
    printw(" _   _ _ __   __| | ___ _ __| |     ___   ___ | | _____  __| |\n"           );
    printw("| | | | '_ \\ / _` |/ _ \\ '__| |    / _ \\ / _ \\| |/ / _ \\/ _` |\n"      );
    printw("| |_| | | | | (_| |  __/ |  | |___| (_) | (_) |   <  __/ (_| |\n");
    printw(" \\__,_|_| |_|\\__,_|\\___|_|   \\_____\\___/ \\___/|_|\\_\\___|\\__,_|\n\n");
    printw("por Lucas Gabriel Batista Lopes\n"                                          );       
    printw("\nDigite alguma tecla para continuar\n\n"                                   );
}

void imprimirTelaFinal(struct Game* game) {
    
    printw("   _____                         ____\n"                      );
    printw("  / ____|                       / __ \\\n"                    );
    printw(" | |  __  __ _ _ __ ___   ___  | |  | |_   _____ _ __\n"      );
    printw(" | | |_ |/ _` | '_ ` _ \\ / _ \\ | |  | \\ \\ / / _ \\ '__|\n");
    printw(" | |__| | (_| | | | | | |  __/ | |__| |\\ V /  __/ |\n"       );
    printw("  \\_____|\\__,_|_| |_| |_|\\___|  \\____/  \\_/ \\___|_|\n"  );
    
    printw("\nVoce chegou na fase %d.\n", game->boneco->fase              );                                         
    printw("Sua pontuacao foi de %04d pontos.\n", game->boneco->pontos    );
    printw("\nDigite 'q' para sair."                                      );
}
