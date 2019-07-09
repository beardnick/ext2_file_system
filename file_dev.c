#include "file_dev.h"
#include "node.h"
#include "type.h"
#include <stdlib.h>
#include "e2fs.h"
#include <string.h>

int read_disk_block(struct ext2_mem_inode* inode , int block, char* buf){
    // struct ext2_disk_inode
}

int file_write(struct ext2_mem_inode *inode, struct file *fp, const char *buf, int count){
}

int file_read(struct ext2_mem_inode *inode, struct file *fp, char *buf, int count){
    int read_count = 0;
    while (read_count < count)
    {
        int block_index = fp->f_pos / DEFAULT_PER_BLOCK_SIZE;
        /* 说明该数据块还没有被加载到内存缓冲链表中,所以马上访问磁盘，将其读入到内存buffer中 */
        if(inode->i_zone[block_index] == 0){
            // char *buf = (char *) malloc(DEFAULT_PER_BLOCK_SIZE);
            struct buffer_node* bnode = (struct buffer_node *) malloc(sizeof(struct buffer_node));
            read_disk_block(inode, block_index, bnode->data);
            global_file_system.btable[inode->buffer_index]->tail->next = bnode;
            global_file_system.btable[inode->buffer_index]->tail = bnode;
            bnode->next = NULL;
            memcpy(buf + read_count, bnode->data, DEFAULT_PER_BLOCK_SIZE);
        }
        else
        { /*数据块已经在缓冲中了 */
            struct buffer_node *p = global_file_system.btable[inode->buffer_index]->head;
            int cnt = 0;
            while (p != NULL && cnt != block_index)
            {
                p++;
                cnt++;
            }
            memcpy(buf + read_count, p->data, DEFAULT_PER_BLOCK_SIZE);
        }
        read_count += DEFAULT_PER_BLOCK_SIZE;
    }
    return 1;
}