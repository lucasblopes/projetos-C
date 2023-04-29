## Cifras de Beale

---

Lucas Gabriel Batista Lopes 
GRR20220062

---

## Uso

```
   (1) Codificar uma mensagem qualquer contida em um arquivo ASCII usando um livro cifra

   ./beale  -e  -b LivroCifra -m MensagemOriginal -o MensagemCodificada -c ArquivoDeChaves 

   (2) Decodificar uma mensagem, usando um arquivo de códigos

   ./beale  -d  -i MensagemCodificada  -c ArquivoDeChaves  -o MensagemDecodificada 

   (3) .Decodificar uma mensagem usando o livro cifra

   ./beale -d -i MensagemCodificada -b LivroCifra -o MensagemDecodificada 
```

# Estrutura e algoritmos do código

# keys.h

Esse módulo contém as funções relacionadas às listas de caracteres, chaves e aos arquivos necessários para o programa. Assim, estão presentas as funções de iniciar e liberar memória das listas, realizar inserções, remoções e busca de nodos, além das funções que montam as listas de chaves e que criam o arquivo de chaves.

A estrutura de dados utilizada para resolver o problema de forma eficiente foi uma lista de chaves dentro de uma lista de caracteres.

Cada nodo da lista de chaves (keyNode) contém os valores de cada caracter, que são nodos (charNode) da lista de caracteres.

- Estrutura das chaves:
```
   struct keyNode {

      struct keyNode* next;
      int value; /* valor da chave */
   };

   struct keyList {

      struct keyNode* head;
      struct keyNode* tail;
      int size;  /* quantidade de chaves por caractere */   
   };
```

- Estrutura dos caracteres:
```
struct charNode {

    struct charNode* next;
    struct keyList* keylist;
    char character;
};

struct charList {

    struct charNode* head;
    struct charNode* tail;
};
```

- Funcionamento dos algoritmos que montam as listas:

__void create_keylist_book(args..)__

Essa função monta a lista de chaves através de um livro cifra lendo caractere por caractere do texto de modo a inserir ordenadamente um nodo caractere na "charList" ao passo que insere as respectivas chaves na cabeça da "keyList", para listar os valores de modo decrescente, respeitando a especificação do trabalho.

__void create_keylist_file(args..)__

Essa função tem o mesmo propósito que a anterior, mas ela já recebe um arquivo de chaves como parâmetro. Assim, basta ler um caractere e inserir um nodo na cauda de "charList" e realizar o mesmo procedimento para as chaves, mantendo as estruturas ordenadas de acordo com o exemplo dado na especificação.

__void create_keyfile(args..)__

Aqui, o programa cria um arquivo de chaves com base nas estruturas de charactere e chaves já criadas. Então basta acessar todos os dados e escreve-los no "ArquivoDeChaves".

# encode.h

Esse bloco é responsável por criar o arquivo "MensagemCodificada", dada uma mensagem original, utilizando as listas de caracteres/chaves já montadas.

O funcionamento do algoritmo funciona utilizando a função encode(args..) e catch_random_key(args..) de modo a ler um caractere da mensagem original e buscar uma chave aleatória presente no "charNode" correspondente ao caractere.

- Dígitos especiais:
```
(-1) : indica um espaço

(-2) : indica uma nova linha

(-3) : indica que o caractere da mensagem não foi encontrado na lista de caracteres
```

# decode.h

Esse bloco é responsável por decodificar uma mensagem dada e criar um arquivo "MensagemDecodificada".

A função decode(args..) realiza isso procurando cada número nas listas de caracteres->chaves utilizando a função find_key(args..) e imprime o caracter encontrado no arquivo "MensagemDecodificada" se a chave foi encontrada. E, caso contrário, a função imprime "(?)" que indica que a chave não está presente nas listas.

