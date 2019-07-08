#ifndef __NAMEI_H
#define __NAMEI_H
#include "type.h"

/* 通过路径来查找文件 */
struct ext2_mem_inode* namei(const char *filename, struct ext2_mem_inode *root);

#endif // !__NAMEI_H