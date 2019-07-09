#include "node.h"
#include <stdlib.h>
#include "e2fs.h"
#include <time.h>
#include <string.h>


struct ext2_mem_inode* get_root_inode(){
    return iget(1);
}

struct ext2_mem_inode *iget(int number){
    if(global_file_system.itable[number] != NULL){
        return global_file_system.itable[number];
    }
    struct ext2_mem_inode* m_node = (struct ext2_mem_inode *) malloc(sizeof(struct ext2_mem_inode));
    struct ext2_disk_inode d_node;
    fseek(global_file_system.fs_file, 1024 * 5 + number * DEFAULT_INODE_SIZE, SEEK_SET);
    fread(&d_node,DEFAULT_INODE_SIZE,1,global_file_system.fs_file);
    // m_node->i_mode = d_node.i_mode;
    // m_node->i_uid = d_node.i_uid;
    // m_node->i_size = d_node.i_size;
    // m_node->i_mtime = d_node.i_time;
    // m_node->i_gid = d_node.i_gid;
    // m_node->i_nlinks = d_node.i_nlinks;
    m_node->i_atime = time(NULL);
    m_node->i_dev = 0;
    m_node->i_num = number;
    memcpy(m_node->i_d_zone, d_node.i_zone, sizeof(d_node.i_zone));
    m_node->buffer_index = get_buffer();
    global_file_system.itable[number] = m_node;
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