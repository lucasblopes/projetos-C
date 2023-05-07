### Árvore AVL

---

- Lucas Gabriel Batista Lopes 
- GRR20220062

---

## Objetivo 

O trabalho consiste em uma implementação da inclusão e da exclusão de valores de uma Árvore AVL na linguagem C. O programa recebe uma sequência de operações seguidas de números inteiros, onde "i" indica a inclusão e "r" a remoção.

- Exemplo de uma entrada válida (stdin):

```
    i 4
    i 6
    i 1
    i 2
    i 7
    i 3
    i 5
    i 8
    r 8
```

- A saída esperada pelo programa (stdout):  

```
    1,2
    2,1
    3,2
    4,0
    5,2
    6,1
    7,2
```

Na saída, os valores antes da vírgula "," estão em ordem crescente, de acordo com a função "inorder", enquanto os valores após a vírgula indicam o nível do nodo para que a árvore esteja balanceada de acordo com as propriedades da AVL. Note que o nível é em relação à raíz (0).

## Uso

```

   ./myavl < teste.in > teste.out

```

## Estrutura de Dados
```c
struct tNode {

    struct tNode *parent;
    struct tNode *right;
    struct tNode *left;
    int key, height;
};
```

## tree.h
```c

/* realiza a inclusao de um nodo em uma arvore avl e realiza o balanceamento, se necessario */
struct tNode *node_insert(struct tNode *node, int key);

/* remove um nodo da arvore avl e realiza o balancemanto, se necessario */
struct tNode *node_remove(struct tNode *node, int key); 

/* realiza a caminhada em ordem na arvore e imprime as chaves */
/* note que level é passado com o valor 0, que é incrementado a cada nível abaixo da raíz */
void inorder_print(struct tNode *node, int level);

/* libera memoria da arvore recursivamente */
void free_tree(struct tNode *node);
```

## Descrição da Implementação

A implementação da AVL foi realizada com base na implementação da árvore BST vista em sala de aula e nos slides. Assim, as principais modificações no código foram a adição da altura na estrutura do nodo e a criação de uma função para manter a árvore balanceada de acordo com as propriedades da AVL.

- Inclusão: 

Para incluir um nodo a função node_insert(args..) realiza uma busca binária para encontrar a posição de inserção, assim como na BST, e, após inserir, atualiza a altura e balanceia as sub-árvores, se necessário, até chegar na raíz. Este processo de "subir até a raiz" é garantida pela natureza recursiva da busca binária implementada. 

- Exclusão: 

O programa realiza a exclusão de um nodo pela função node_remove(args..) que, assim como na inclusão, realiza uma busca binária recursiva até encontrar o nodo a ser excluído. Após essa etapa, o programa utiliza duas estratégias de remoção, de acordo com o número de filhos do nodo:

1- Nodo possui no máximo 1 filho:
    
Nesse caso, o programa chamará a função transplant(args..) que irá trocar o nodo com o seu filho (se existir), atualizando as suas hierarquias pai-filho. Depois disso, irá liberar memória do nodo e retornar o filho (ou NULL, caso não tenha).

2 - Nodo possui 2 filhos:

Aqui, o nodo receberá a chave do seu antecessor e irá remover o antecessor chamando a função node_remove(args..) novamente. Note que essa chamada cairá no caso 1, pois o antecessor possui no máximo 1 filho.
Após a exclusão do nodo, assim como na inclusão, o programa atualiza a altura e balanceia a árvore, se necessário.

- Algoritmo de Balanceamento:

O programa verifica se uma sub-árvore está desbalanceada de acordo com o seu "fator de balanceamento", que consiste na diferença da altura entre dois nós irmãos. Se essa subtração for maior que 1 ou menor que -1, é necessário realizar rotações em cada caso para que esse fator esteja contida no intervalo [-1, 1]. A função tree_balance(args..) cobre todos os casos:

Note: as funções de rotação já atualizam as alturas dos nodos envolvidos.

```c
struct tNode* tree_balance(struct tNode* node) {

    /* ROTAÇÃO ESQUERDA */
    if (balance_factor(node) < -1 && balance_factor(node->right) <= 0) { 
        return left_rotation(node);
    }

    /* ROTAÇÃO DIREITA */
    if (balance_factor(node) > 1 && balance_factor(node->left) >= 0) { 
        return right_rotation(node);
    }

    /* ROTAÇÃO ESQUERDA DIREITA */
    if (balance_factor(node) > 1 && balance_factor(node->left) < 0) { 
        node->left = left_rotation(node->left);
        return right_rotation(node);
    }

    /* ROTAÇÃO DIREITA ESQUERDA */
    if (balance_factor(node) < -1 && balance_factor(node->right) > 0) { 
        node->right = right_rotation(node->right);
        return left_rotation(node);
    }

    return node;
}
```



