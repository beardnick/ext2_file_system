#ifndef __FILE_DEV_H
#define __FILE_DEV_H

#include "node.h"
#include "file.h"

int file_write(struct m_inode *inode, struct file *fp, char *buf, int count);

int file_read(struct m_inode *inode, struct file *fp, char *buf, int count);


#endif // !