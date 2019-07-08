#ifndef __FILE_DEV_H
#define __FILE_DEV_H

#include "node.h"
#include "file.h"

int file_write(struct ext2_mem_inode *inode, struct file *fp, const char *buf, int count);

int file_read(struct ext2_mem_inode *inode, struct file *fp, char *buf, int count);


#endif // !