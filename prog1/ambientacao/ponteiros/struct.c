#include<stdio.h>

struct horario{
    int hora;
    int minuto;
    int segundo;
};

int main(){
    struct horario agora, *depois;
    depois = &agora;

    //-> para um ponteiro apontar para um membro da struct
    depois->hora = 12;
    depois->minuto = 23;
    depois->segundo = 03;

    printf("%d:%d:%d", agora.hora, agora.minuto, agora.segundo);
    
    return 0;
}