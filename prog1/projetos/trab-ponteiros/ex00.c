#include<stdio.h>

//printa o endereço de m
int main(){
    int m, n, o, *z;

    m = 10;
    
    printf("endereco de m: %p\n", &m);

    z = &m;
    printf("z apontando para m: %p\n", z);

    printf("valor armazenado no endereço apontado por z: %d\n", *z);

    printf("endereco de n: %p\n", &n);

    o = m;
    printf("o recebe valor de m: o = %d\n", o);

    printf("endereco de z: %p\n", &z);

    //&n = &o : isso nao eh possivel pois os enderecos das variaveis sao fixos!
    printf("[ERRO!] endereco de n recebe o endereco de o: (enderecos sao fixos) \n");

    n = (int *)&o; //warning! Pois sao tipos incompativeis (int x int*)
    printf("[WARNING!] n recebe o endereco de o: %p\n ", n);
    
    return 0;
}