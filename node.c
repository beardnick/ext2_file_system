#include "node.h"
#include <stdlib.h>
#include "e2fs.h"
#include <time.h>
#include <string.h>


struct ext2_mem_inode* get_root_inode(){
    printf("get_root_inode()\n");
    return iget(1);
}

struct ext2_mem_inode *iget(int number){
    printf("iget %d\n", number);
    if (global_file_system.itable[number] != NULL)
    {
        return global_file_system.itable[number];
    }
    struct ext2_mem_inode* m_node = (struct ext2_mem_inode *) malloc(sizeof(struct ext2_mem_inode));
    struct ext2_disk_inode d_node;
    printf("文件系统 %p\n", global_file_system.fs_file);
    fflush(global_file_system.fs_file);
    if (fseek(global_file_system.fs_file, 1024 * 5 + number * DEFAULT_INODE_SIZE, SEEK_SET) == 0)
    {
        printf("fseek成功, %ld\n", ftell(global_file_system.fs_file));
    }
    printf("fseek\n");
    fread(&d_node,DEFAULT_INODE_SIZE,1,global_file_system.fs_file);
    printf("fread\n");
    m_node->i_mode = d_node.i_mode;
    // printf("i_mode %d\n", m_node->i_mode);
    m_node->i_uid = d_node.i_uid;
    m_node->i_size = d_node.i_size;
    m_node->i_mtime = d_node.i_time;
    m_node->i_gid = d_node.i_gid;
    m_node->i_nlinks = d_node.i_nlinks;
    m_node->i_atime = time(NULL);
    m_node->i_dev = 0;
    m_node->i_num = number;
    // memcpy(m_node->i_d_zone, d_node.i_zone, sizeof(d_node.i_zone));
    for (int i = 0; i < 9; i++)
    {
        m_node->i_d_zone[i] = d_node.i_zone[i];
    }
    printf("m_node-> i_num %d\n", m_node->i_num);
    m_node->buffer_index = get_buffer();
    printf("buffer_index = %d\n", m_node->buffer_index);
    printf("before itable\n");
    global_file_system.itable[number] = m_node;
    printf("after itable\n");
    return m_node;
}

struct ext2_disk_inode to_disk(struct ext2_mem_inode m_node){
    struct ext2_disk_inode d_node;
    d_node.i_mode = m_node.i_mode;
    d_node.i_uid = m_node.i_uid;
    d_node.i_size = m_node.i_size;
    d_node.i_time = m_node.i_mtime;
    d_node.i_gid = m_node.i_gid;
    d_node.i_nlinks = m_node.i_nlinks;
    memcpy(d_node.i_zone, m_node.i_d_zone,sizeof(m_node.i_d_zone));
    return d_node;
}

struct ext2_mem_inode to_mem(struct ext2_disk_inode d_node){
    struct ext2_mem_inode m_node;
    m_node.i_mode = d_node.i_mode;
    m_node.i_uid = d_node.i_uid;
    m_node.i_size = d_node.i_size;
    m_node.i_mtime = d_node.i_time;
    m_node.i_gid = d_node.i_gid;
    m_node.i_nlinks = d_node.i_nlinks;
    memcpy(m_node.i_d_zone, d_node.i_zone, sizeof(d_node.i_zone));
    return m_node;
}