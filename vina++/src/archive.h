#ifndef ARCHIVE_H
#define ARCHIVE_H

#include <stdio.h>
#include <stdlib.h>

#include "directory.h"

int archive_directory_read(struct Directory *dir);

int archive_insert(struct Directory *dir, const char *path, int flag_i);

int archive_extract(struct Directory *dir, char *path);

int archive_remove(struct Directory *dir, long index);

int archive_directory_write(struct Directory *dir);

#endif

