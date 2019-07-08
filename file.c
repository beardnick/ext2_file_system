#include "file.h"
#include "node.h"
#include "namei.h"
#include "file_dev.h"
#include <stdlib.h>


struct file* sys_open(const char* filename, int flag, int mode){
    struct ext2_mem_inode* root = global_files_struct.root;
    struct ext2_mem_inode f_node = namei(filename, root);
    struct file *target = (struct file *) malloc(sizeof(struct file));
    if (f_node.i_mode == __S_IFREG || f_node.i_mode == __S_IFDIR)
    {
        struct file_operations* fop =(struct file_operations* ) malloc(sizeof(struct file_operations));
        fop->write = file_write;
        fop->read = file_read;
        target->f_op = fop;
    }
    return target;
}

int get_fd(struct files_struct f_struct){
    for (int i = 0; i < NR_OPEN; i++)
    {
        if (f_struct.fd[i] == NULL)
        {
            return i;
        }
    }
    return -1;
}
