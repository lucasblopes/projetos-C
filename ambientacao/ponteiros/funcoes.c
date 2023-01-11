#include<stdio.h>

void testVariavel(int x){
    ++x;
};

void testPonteiro(int *ptr_x){ //passa com * pois queremos o valor aqui
    ++*ptr_x;
};

int main(){
    int test = 1;
    int *ptr_test = &test;

    //testVariavel(test);
    testPonteiro(ptr_test); //passa sem o * pois queremos passar o endereço 

    printf("%d\n", test);

    return 0;
}