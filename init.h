#ifndef __INIT_H
#define __INIT_H

#include "type.h"
#include <stdio.h>

struct ext2_super_block init_super_block();

FILE* mkfs(const char *fs_dir, const char *fs_size);


#endif