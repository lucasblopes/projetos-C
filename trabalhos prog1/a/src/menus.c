#include <ncurses.h>

#include "tipos.h"

void imprimirLogo(void){

    printw("                 _            _____            _            _ \n"           );
    printw("                | |          / ____|          | |          | |\n"           );
    printw(" _   _ _ __   __| | ___ _ __| |     ___   ___ | | _____  __| |\n"           );
    printw("| | | | '_ \\ / _` |/ _ \\ '__| |    / _ \\ / _ \\| |/ / _ \\/ _` |\n"      );
    printw("| |_| | | | | (_| |  __/ |  | |___| (_) | (_) |   <  __/ (_| |\n");
    printw(" \\__,_|_| |_|\\__,_|\\___|_|   \\_____\\___/ \\___/|_|\\_\\___|\\__,_|\n\n");       
    printw("\nDigite qualquer tecla para continuar\n\n"                                   );
}

void imprimirInstrucoes(){

    printw("\n -INSTRUCOES- \n\n\n");
    printw("Utilize as teclas 'w','a','s','d' ou as setas do teclado para se movimentar.\n\n");
    printw("O seu objetivo eh montar as receitas dos lanches de acordo com a ordem de chegada dos clientes.\n\n");
    printw("Voce pode descartar uma receita se movendo ate a lixeira (o) e entregar um pedido no balcao (@).\n\n");
    printw("Voce tem um total de 6 vidas e o descarte de uma receita acarretara na perca de 1 vida, enquanto a entrega errada de um pedido acarretara na perca de 2 vidas.\n\n");
    printw("Quanto maior for a quantidade de ingredientes para fazer o pedido, maior sera a pontuacao atrelada ao pedido.\n\n");
    printw("Ao completar uma leva de pedidos, voce ira avancar de fase e sera recompensado com 20 pontos. A cada fase o numero de clientes aumenta. \n\n");
    printw("\nBom jogo :D\n\n\n");
    printw("Digite qualquer tecla para continuar\n\n");
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
    printw("Game criado por Lucas Gabriel Batista Lopes\n"                );
    printw("\nDigite 'q' para sair."                                      );
}
