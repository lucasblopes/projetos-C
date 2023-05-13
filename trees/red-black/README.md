### Árvore RED BLACK

---

- Lucas Gabriel Batista Lopes 

---

## Objetivo 

O trabalho consiste em uma implementação da inclusão e da exclusão de valores de uma Árvore Red Black na linguagem C. O programa recebe uma sequência de operações seguidas de números inteiros, onde "i" indica a inclusão e "r" a remoção.

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

   ./myrb < teste.in > teste.out

```

## Estrutura de Dados
```c
struct tNode {

    struct tNode *parent;
    struct tNode *right;
    struct tNode *left;
    int key, color;
};
```

