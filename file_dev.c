#include "file_dev.h"
#include "node.h"
#include "type.h"
#include <stdlib.h>
#include "e2fs.h"
#include <string.h>
#include "file.h"

int read_disk_block(struct ext2_mem_inode* inode , int block, char* buf){
    fseek(global_file_system.fs_file,
     1024 * 5 +
      global_file_system.super_block.s_inode_size * global_file_system.super_block.s_inodes_count
       + DEFAULT_PER_BLOCK_SIZE * inode->i_d_zone[block],
      SEEK_SET);
    fread(buf, DEFAULT_PER_BLOCK_SIZE, 1, global_file_system.fs_file);
    return 1;
}

int file_write(struct ext2_mem_inode *inode, struct file *fp, const char *buf, int count){
    printf("写inode %d\n", inode->i_num);
    int write_count = 0;
    while (write_count < count)
    {
        int block_index = fp->f_pos / DEFAULT_PER_BLOCK_SIZE;
        // #TODO 2019-07-09 实现间接索引
        struct buffer_node* new_node =  get(inode->buffer_index, block_index);
        memcpy(new_node->data, buf, DEFAULT_PER_BLOCK_SIZE);
        new_node->block = inode->i_d_zone[block_index];
        inode->i_zone[block_index] = block_index;
        write_count += DEFAULT_PER_BLOCK_SIZE;
        block_index++;
    }
    return 1;
}

int file_read(struct ext2_mem_inode *inode, struct file *fp, char *buf, int count){
    int read_count = 0;
    while (read_count < count)
    {
        int block_index = fp->f_pos / DEFAULT_PER_BLOCK_SIZE;
        // #TODO 2019-07-09 实现间接索引
        /* 说明该数据块还没有被加载到内存缓冲链表中,所以马上访问磁盘，将其读入到内存buffer中 */
        if(inode->i_zone[block_index] == 0){
            // char *buf = (char *) malloc(DEFAULT_PER_BLOCK_SIZE);
            struct buffer_node* bnode = (struct buffer_node *) malloc(sizeof(struct buffer_node));
            memset(bnode, 0, sizeof(struct buffer_node));
            read_disk_block(inode, block_index, bnode->data);
            bnode->block = inode->i_d_zone[block_index];
            global_file_system.btable[inode->buffer_index].tail->next = bnode;
            global_file_system.btable[inode->buffer_index].tail = bnode;
            bnode->next = NULL;
            memcpy(buf + read_count, bnode->data, DEFAULT_PER_BLOCK_SIZE);
        }
        else
        { /*数据块已经在缓冲中了 */
            struct buffer_node *p = global_file_system.btable[inode->buffer_index].head;
            int cnt = 0;
            while (p != NULL && cnt != block_index)
            {
                p = p->next;
                cnt++;
            }
            memcpy(buf + read_count, p->data, DEFAULT_PER_BLOCK_SIZE);
        }
        read_count += DEFAULT_PER_BLOCK_SIZE;
        block_index++;
    }
    return 1;
}