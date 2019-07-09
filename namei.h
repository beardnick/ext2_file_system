#ifndef __NAMEI_H
#define __NAMEI_H
#include "type.h"
#include "file.h"
#include "node.h"

/* 通过路径来查找文件 */
struct ext2_mem_inode* namei(const char *filename, struct ext2_mem_inode *root);

int get_subfiles(struct ext2_mem_inode *parent, struct ext2_dir_entry sub_files[]);

#endif // !__NAMEI_H