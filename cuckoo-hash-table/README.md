### CUCKOO HASH TABLE

---

- Lucas Gabriel Batista Lopes 
- GRR20220062

---

## Objetivo 

O trabalho consiste em uma implementação da inclusão e da exclusão de valores de uma Tabela Hash na linguagem C. O programa recebe uma sequência de operações seguidas de números inteiros, onde "i" indica a inclusão e "r" a remoção.

- Exemplo de uma entrada válida (stdin):

```
    i 10
    i 22
    i 4
    i 15
    i 59
    r 15
    r 22
    r 59
```

- A saída esperada pelo programa (stdout):  

```
    4,T2,6
    10,T1,10
```

Na saída, cada linha é composta pelo valor presente na tabela (T1 ou T2) e a posição na respectiva tabela hash.

## Uso

```

   ./myht < teste.in > teste.out

```

## Estrutura de Dados
```c
    struct Table {
        int key;
        int table;      /* table 1 ou 2 */
        int position;   /* -1 indica que está vazio e -2 indica que est no estado excluído */
    };
```

## Descrição da Implementação


- Tabela Hash 1 e 2:

As duas tabelas foram implmentadas por vetores do tipo struct Table, como mencionado acima, de tamanho estático m, que foi especificado no trabalho. No início do programa todas as posições desses vetores são inicializados com key = 0, table = 0 e position = -1, para manter a segurança do programa e facilitar com a manipulação desses vetores posteriormente.

- Funções de Hash:

h1(key) = (k mod m) e h2(key) = (⌊m * (k * 0.9 − ⌊k * 0.9⌋)⌋) são as funções de hash especificadas no trabalho, que retornam a posição esperada de key para cada tabela.

- Busca:

A função de busca leva em consideração o membro position de cada slot do vetor. Se a posição for -1 indica que está vazia e o valor não está em nenhuma tabela, se for -2 indica que havia um membro na T1 mas ele foi removido. Essa marcação é importante pois podem existir chaves inseridas na T2 que dependem da busca realizada em T1, e se essa busca retornar "-2", o valor pode estar presente na T2. 
Com base nessas considerações, a busca retorna o membro encontrado por h1(key) ou h2(key), e como existe o membro table, basta acessá-lo para verificar em qual tabela o valor está presente.

- Inserção:

A inserção inicia-se com uma busca pelo valor. Se a posição do membro retornado pela busca for -1 ou -2 o programa insere na tabela 1, já que a posição está livre. Caso contrário, ocorreu uma colisão e ele move a chave que estava na posição que a nova chave vai ocupar na tabela 1 para a tabela 2 e insere a nova chave na tabela 1.

- Remoção:

Assim como na inserção, ele inicia a remoção fazendo uma busca, e se a posição do membro retornado pela busca for diferente de -1 ou -2, quer dizer que encontrou o chave em alguma tabela e deve prosseguir. Após isso a função verifica se o valor retornado pertence a tabela 1 e se a chave do membro é igual a chave que deve ser removida. Caso isso seja verdade, ele remove a chave, zerando o seu valor e atribuindo -1 a sua posição. Caso a chave esteja na tabela 1, ele atribui a posição à -2, indicando que está no estado excluído.

- Impressão do resultado: 

Para garantir que o resultado final seja impresso ordenado com a seguinte ordem de precedência: key > table > position, a função cria um vetor temporário e recebe todos os valores inseridos em T1 e T2 e os ordena com base na precedência citada, utilizando a função qsort(). Depois disso, é impresso os valores já ordenados do vetor temporário.


