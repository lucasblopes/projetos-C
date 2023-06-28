#ifndef TOOLS_H
#define TOOLS_H

#include <stdlib.h>
#include <stdio.h>

void print_help();

int copy_file(FILE *write, FILE *read, long write_pos, long read_pos, size_t size);

FILE *create_file(char *path);

int long_compare(const void *a, const void *b);

void print_mode(mode_t mode) ;

#endif

