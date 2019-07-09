#include "file.h"
#include "node.h"
#include "namei.h"
#include "file_dev.h"
#include <stdlib.h>
#include "e2fs.h"
#include <string.h>
#include <time.h>

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

int create(char* path , char* filename, int filetype){
    struct ext2_mem_inode* m_node = (struct ext2_mem_inode*) malloc(sizeof(struct ext2_mem_inode));
    struct file* new_file = (struct file*) malloc(sizeof(struct file));
    m_node->i_num = get_free_disk_inode();
    m_node->i_mode = filetype;
    m_node->i_uid = 0;
    m_node->i_size = 0;
    m_node->i_mtime = time(NULL);
    m_node->i_gid = 0;
    m_node->i_nlinks = 0;
    struct ext2_mem_inode *parent = namei(path, get_root_inode());
    struct file* parent_dir = (struct file*) malloc(sizeof(struct file));
    parent_dir->f_pos = parent->i_size;
    char buf[1024];
    struct ext2_dir_entry new_entry;
    new_entry.inode = m_node->i_num;
    memcpy(new_entry.name, filename,strlen(filename));
    memcpy(buf, &new_entry, sizeof(new_entry));
    parent->i_size += sizeof(new_entry);
    file_write(parent, parent_dir, buf, sizeof(new_entry));
    return 1;
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
    struct file *fp = global_files_struct.fd[fd];
    fp->f_op->write(fp->f_inode, fp, buf, count);
    return 1;
}

int sys_read(int fd, char* buf, int count){
    struct file *fp = global_files_struct.fd[fd];
    fp->f_op->read(fp->f_inode, fp, buf, count);
    return 1;
}

