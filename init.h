#ifndef __INIT_H
#define __INIT_H

#include "type.h"
#include <stdio.h>

void init_super_block();

FILE* mkfs(const char *fs_dir, const char *fs_size);


#endif