#include "file.h"
#include "node.h"
#include "namei.h"
#include "file_dev.h"
#include <stdlib.h>


int sys_open(const char* filename, int flag, int mode){
    struct ext2_mem_inode* root = global_files_struct.root;
    struct ext2_mem_inode* f_node = namei(filename, root);
    struct file *target = (struct file *) malloc(sizeof(struct file));
    if (f_node->i_mode == __S_IFREG || f_node->i_mode == __S_IFDIR)
    {
        struct file_operations* fop =(struct file_operations* ) malloc(sizeof(struct file_operations));
        fop->write = file_write;
        fop->read = file_read;
        target->f_op = fop;
    }
    target->f_pos = 0;
    int fd = get_fd();
    global_files_struct.fd[fd] = target;
    return fd;
}

int get_fd(){
    for (int i = 3; i < NR_OPEN; i++)
    {
        if (global_files_struct.fd[i] == NULL)
        {
            return i;
        }
    }
    return -1;
}


int sys_write(int fd, char* buf, int count){
    struct file *file = global_files_struct.fd[fd];
    file->f_op->write(file->f_inode, file, buf, count);
    return 1;
}

int sys_read(int fd, char* buf, int count){
    struct file *file = global_files_struct.fd[fd];
    file->f_op->read(file->f_inode, file, buf, count);
    return 1;
}

