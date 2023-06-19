#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define m 11 /* TAM */

struct Table {
    int key;
    int table;      /* table 1 ou 2 */
    int position;   /* -1 indica que está vazio e -2 indica que est no estado excluído */
};

int h1(int key) {

    return (key % m);
}

int h2(int key) {

    return floor(m * (key * 0.9 - floor(key * 0.9)));
}

void init_table(struct Table* table, int size) {

    for(int i = 0; i < size; i++) {
        table[i].key = 0;
        table[i].table = 0;
        table[i].position = -1; /* vazio */
    }
}

struct Table* search_key(struct Table* table1, struct Table* table2, int key) {

    int hash1 = h1(key);
    int hash2 = h2(key);

    if (table1[hash1].position == -1) { /* chave não encontrada (posição vazia) */
        return &table1[hash1];
    }
    if (table1[hash1].key == key) {     /* chave presente em T1 */
        return &table1[hash1];
    }
    if (table2[hash2].key == key) {     /* chave presente na T2 */
        return &table2[hash2];
    }
    if (table1[hash1].position == -2) { /* estado excluido em T1 */
        if (table2[hash2].key == key) { /* mas presente em T2 */
            return &table2[hash2];
        }
    }
    return &table1[hash1]; /* estado excluido em T1 e não presente em T2 */
}

void insert_key(struct Table* table1, struct Table* table2, int key) {

    int hash1 = h1(key);
    struct Table* entry = search_key(table1, table2, key);
    int pos = entry->position;

    if (entry->key == key) /* evita duplicatas */
        return;

    if (pos == -1 || pos == -2) { /* está vazio ou foi excluído (insere na T1) */
        table1[hash1].key = key;
        table1[hash1].table = 1;
        table1[hash1].position = hash1;
    } else { /* colisao em T1 */
        int key_i = entry->key;
        int hash2 = h2(key_i);
        table2[hash2].key = key_i;
        table2[hash2].table = 2;
        table2[hash2].position = hash2;
        table1[hash1].key = key;
    }
}

void remove_key(struct Table* table1, struct Table* table2, int key) {
    
    struct Table* remove = search_key(table1, table2, key);
    int pos = remove->position;
    
    if (pos == -1 || pos == -2) {
        return;
    }

    if (remove->table == 2 && remove->key == key) { /* exclui da tabela 2 */
        table2[pos].table = 0;
        table2[pos].position = -1;
    } else if (remove->table == 1 && remove->key == key) {
        table1[pos].table = 0;
        table1[pos].position = -2; /* posição excluída */
    }
}

int table_compare(const void *a, const void *b) {

    struct Table *table_a = (struct Table *)a;
    struct Table *table_b = (struct Table *)b;

    /* ordena por key */
    if (table_a->key != table_b->key) {
        return table_a->key - table_b->key;
    }
    /* ordena por table */
    if (table_a->table != table_b->table) {
        return table_a->table - table_b->table;
    }
    /* ordena por position */
    return table_a->position - table_b->position;
}

void print_table(struct Table* table1, struct Table* table2) {
    
    struct Table temp[2*m];
    init_table(temp, 2*m);

    for (int i = 0; i < m; i++) {
        if (table1[i].table != 0) {
            temp[i].key = table1[i].key;
            temp[i].table = table1[i].table;
            temp[i].position = table1[i].position;
        }
    }
    
    for (int i = 0; i < m; i++) {
        if (table2[i].table != 0) {
            temp[i].key = table2[i].key;
            temp[i].table = table2[i].table;
            temp[i].position = table2[i].position;
        }
    }

    qsort(temp, 2*m, sizeof(struct Table), table_compare);

    for (int i = 0; i < 2*m; i++) {
        if (temp[i].table != 0) {
            printf("%d,T%d,%d\n", temp[i].key, temp[i].table, temp[i].position);
        }
    }
}

int main() {

    struct Table table1[m];
    struct Table table2[m];
    char op;
    int key;

    init_table(table1, m);
    init_table(table2, m);

    while (scanf("%c %d", &op, &key) != EOF) {
        if (op == 'i')
            insert_key(table1, table2, key);
        else if (op == 'r')
            remove_key(table1, table2, key);
        getchar(); /* '/n' */
    }

    print_table(table1, table2);

    return 0;
}