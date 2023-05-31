#include <stdio.h>
#include "generic.h"

int char_cmp(void* a, void* b) {

    return *(char*) a - *(char*) b;
}

int int_cmp(void* a, void* b) {

    return *(int*) a - *(int*) b;
}

int float_cmp(void* a, void* b) {

    return *(float*) a - *(float*) b;
}

int double_cmp(void* a, void* b) {

    return *(double*) a - *(double  *) b;
}

void float_print(void *data) {

	printf("%f", *((float *) data));
}

void double_print(void *data) {

	printf("%lf", *((double *) data));
}

void char_print(void *data) {

	printf("%c", *((char *) data));
}

void int_print(void *data) {

	printf("%d", *((int*) data));
}

void str_print(void *data) {

	printf("%s", ((char *) data));
}
