typedef struct Data {
    int dia, mes, ano;
}Data;

typedef struct Horario {
    int hora_inicial, min_inicial, hora_final, min_final;
} Horario;

typedef struct compromisso {
    Data *data;
    Horario *horario;
    char *evento;
    int id;
    struct compromisso *proximo;
} compromisso;

typedef struct Agenda {
    compromisso *inicio;
} Agenda;

void inicializarAgenda();

void listarCompromissos();

int horarioLivre();

compromisso *criarCompromisso();

void adicionarCompromisso();

int ehDepois();

void atualizarID();

void removerCompromisso();

void destruirAgenda();