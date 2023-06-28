## Arquivador Vina++

---

- Lucas Gabriel Batista Lopes 
- GRR20220062

---

## Uso

```
    ./vina++ <opção> <archive> [membro1 membro2 ...]
```

# Estrutura de dados e algoritmos

```c
struct Directory {
    FILE* archive;      /* ponteiro para o archive */
    struct Member *m;   /* vetor para as propriedades dos membros */ 
    int modified;       /* se o archive foi modificado atualiza o diretório no final */
    char* path;         /* nome do archive */
    long pos;           /* posição do diretório no archive */
    long n;             /* número de membros */
};

struct Member { 
    char *path;
    int plength;        /* tamanho do path */
    long order;         /* ordem de inserção */
    long pos;           /* posição do membro no archive */
    uid_t uid;          /* user id */
    mode_t mode;        /* permissões */
    size_t size;        /* tamanho do membro */
    time_t mtime;       /* data de modificação */
};
```

A estrutura de dados utilizada foi a "Directory", que armazena um vetor do tipo "struct Member" que contém todos as propriedades requisitadas na especificação do trabalho. Além disso, directory possui um ponteiro que aponta para o archive, para que não seja necessário passar o FILE* como parâmetro de funções, o mesmo foi feito com o caminho (path) do archive. Ele também possui o membro "pos", que indica a posição do início do diretório no archive, o que se faz necessário para quando for ler o diretório do archive ou atualiza-lo na posição correta.

# directory.h

Esse bloco é responsável por manipular o diretório, ou seja, todas as funções presentes nele manipulam o diretório na memória ram. Suas principais funções são: 

__directory_insert(struct Directory* dir, struct stat st_file, const char* path)__

Essa função insere um membro ao final do vetor de membros, garantindo que todas as suas propriedades sejam preenchidas.

__directory_search_path(struct Directory* dir, const char* path)__

Essa função faz uma busca sequencial com base no path de cada membro e retorna o seu índice.

__directory_move(struct Directory* dir, long dest, long src)__

Essa função é chamada quando o programa é executado com a opção move: vina++ -m <target> <archive> <membro>
Dessa forma, ela faz uma movimentação dos membros do vetor do diretório com o objetivo de mover o membro para frente do target.
Como directory_move() recebe dois indíces como parâmetro, dest e src, onde src é o índice do membro que será movido e dest é o seu índice após a movimentação, a função é chamada com o índice de target + 1 e o índice do membro, que são retornados pela directory_search_path().

__directory_list(struct Directory* dir)__ 

Essa função é chamada quando o programa é executado com a opção de listagem: vina++ -c <archive>
O seu funcionamento é simples, ela apenas itera no vetor de membros do diretório imprimindo as seguintes propriedades: 
permissões, id do usuário, tamanho do arquivo, ordem de inserçãoe, data de modificação e o seu caminho. 
Essa função foi baseada no tar com as opções tvf, como especificado no trabalho.

# archive.h

Esse bloco é responsável por manipular funções que escrevem diretamente no archive, ou seja, manipulam o arquivo no HD, com funções como fread() e fwrite(). Suas principais funções são:

__archive_directory_read(struct Directory* dir)__

Caso o programa seja executado com um archive válido em <archive>, o diretório será lido ao final do archive e será alocado na memória ram para realizar as operações necessárias.

__archive_insert(struct Directory* dir, const char* path, int flag_i)__

Essa função é responsável pelas execuções em modo -i e -a: vina++ -i <archive> [membro1, membro2, ...] e funciona da seguinte maneira:
-Faz uma busca para verificar se o membro especificado já não está presente no archive. 
-Caso ele não esteja, o arquivo externo é aberto e copiado ao final do archive, com auxílio da função copy_file();
-Caso ele esteja presente, se foi executado com a opção -i, ou com a opção -a e o arquivo externo for mais recente que o presente no archive, ele será substituido da seguinte maneira:
1) Remove o membro do archive, chamando a função archive_remove().
2) Insere novamente ao final do archive.
3) Move ele para a sua posição original no vetor de membros do diretório, chamando a função directory_move().

__archive_extract(struct Directory* dir, char* path)__

Essa função é responsável pela execução em modo -x: vina++ -x <archive> [membro1, membro2, ...], para extrair membros específicos, ou vina++ -x <archive>, para extrair todos os membros do archive.
Ela funciona de modo a criar um novo arquivo e copiar o conteúdo do membro especificado (ou o da iteração atual, para quando extrair todos os membros) nele. Isso é garantido ao chamar a função create_file(), que garante que seja criado uma hierarquia de diretórios no caminho relativo e retorna o arquivo aberto no caminho correto, para ser feito a cópia com copy_file().

__archive_remove(struct Directory* dir, long index)__

Essa função é responsável pela execução em modo -r: vina++ -x <archive> [membro1, membro2, ...]
É responsável por remover o conteúdo do membro especificado do archive e a sua posição no vetor do diretório. 
Ela faz isso abrindo um novo stream para o archive, responsável por reescrever os membros na posição do que será excluído. Assim, em um loop, ele chama copy_file() para copiar todos os arquivos que estão escritos após o membro excluído size posições para a esquerda, sendo size o tamanho do membro removido. Ao final do processo, chama-se a função ftruncate() para redimensionar o archive ao novo tamanho.

# tools.h

Módulo reservado para funções auxiliares. As principais são:

__copy_file(FILE* write, FILE* read, long write_pos, long read_pos, size_t size)__

Essa função recebe dois arquivos, um que um para leitura e outro para escrita, assim como as suas posições iniciais de leitura/escrita e o tamanho da cópia. Ele faz isso utilizando as funções fread() e fwrite(), e utiliza um buffer de no máximo 1024 bytes, como especificado pelo trabalho.

__create_file(char* path)__

Como já citada anteriormente, essa função primeiramente cria uma string chamada relative_path, garantindo que "./" seja concatenado no início de path para os diretórios no caminho relativo à localização do archive. Após isso, chama-se a função create_directory_hierarchy(), que cria todos os diretórios de path, utilizando mkdir(). Ao final desse processo, create_file() retorna um ponteiro para arquivo em modo de escrita, já que será utilizado pela função de extração.

# Alternativas de implementações experimentadas e dificuldades 

A primeira versão desse trabalho foi feita utilizando arquivos temporários para realizar a substituição e a remoção. Essa foi a primeira maneira que pensei em implementar, mas fui informado que essa estratégia estava vetada da especificação e então refiz o projeto e essa se tornou a versão final do vina++. Nessa nova implementação, a minha maior dificuldade foi fazer a função de remoção se comportar idealmente em todos os casos testados. Como eu optei por manter a ordem dos membros no diretório após a substituição, tive que modificar a remoção para suportar essa feature. A minha estratégia foi criar um vetor auxiliar para armazenar a ordem de inserção de todos os membros, e depois ordenar esse vetor. Depois disso, a função itera em todos os membros do vetor auxiliar e só começa a sobrescrever quando a ordem do membro atual for maior que a do membro que será excluído. Além disso, para ter acesso ao membro do diretório que possui a ordem da vez, fiz uma função de busca com base na ordem do membro, directory_search_order(), que retorna o índice do membro que possui tal ordem para acessar às propriedades corretas desse membro, como tamanho e posição no archvie. Isso garante que todos os membros que foram escritos após o que será removido sejam movidos na ordem correta, sem sobrescrever ninguém e sem deixar nenhum arquivo de fora.