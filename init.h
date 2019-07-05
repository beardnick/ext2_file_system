#ifndef __INIT_H
#define __INIT_H

#include "type.h"
#include <stdio.h>

struct ext2_file_system mkfs(const char *fs_dir, const char *fs_size);

void init_to_zero(struct ext2_file_system* fs);

void init_boot_block(struct ext2_file_system* fs);

void init_super_block(struct ext2_file_system* fs);

void init_bitmap(struct ext2_file_system* fs);

void init_blockmap(struct ext2_file_system* fs);

void init_grp_description(struct ext2_file_system *fs);

void write_origin_data(struct ext2_file_system *fs);


#endif