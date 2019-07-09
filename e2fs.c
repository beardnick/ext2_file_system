#include "e2fs.h"
#include "buffer.h"
#include <stdlib.h>
#include "type.h"
#include "node.h"

int get_buffer(){
    for (int i = 1; i < NR_BUFFER ; i++)
    {
        if(global_file_system.btable[i].head == NULL){
            return i;
        }
    }
    return 0;
}




struct buffer_node* get(int buffer_head, int buffer){
    struct buffer_node *p;
    struct buffer_head_tail head = global_file_system.btable[buffer_head];
    p = head.head;
    int cnt = 0;
    while (cnt != buffer)
    {
        if(p == NULL){
            p = (struct buffer_node *)malloc(sizeof(struct buffer_node));
        }
        p = p->next;
        cnt++;
    }
    return p;
}

int get_free_disk_block(){
    char* map = global_file_system.blockmap;
    char base = 1;
    for (int i = 0; i < 1024; i++)
    {
        if(map[i] != -1){
            for (int j=0; j < 8; j++)
            {
                if((base & map[i]) == 0){
                    return j + i * 8;
                }
                base <<= 1;
            }
        }
    }
    return 0;
}

int get_free_disk_inode(){
    char* map = global_file_system.bitmap;
    char base = 1;
    for (int i = 0; i < 1024; i++)
    {
        if(map[i] != -1){
            for (int j=0; j < 8; j++)
            {
                if((base & map[i]) == 0){
                    return j + i * 8;
                }
                base <<= 1;
            }
        }
    }
    return 0;
}

/* 将内存中的内容回写回磁盘 */
int sync(){
    /*回写超级块 */
    fseek(global_file_system.fs_file, 1024 * 1 , SEEK_SET);
    fwrite(&global_file_system.super_block, 1024, 1, global_file_system.fs_file);
    // /* 回写组块描述符 */
    // fseek(global_file_system.fs_file, 1024 * 2 , SEEK_SET);

    /* 回写blockmap */
    fseek(global_file_system.fs_file, 1024 * 3 , SEEK_SET);
    fwrite(&global_file_system.blockmap, 1024, 1, global_file_system.fs_file);
    /* 回写bitmap */
    fseek(global_file_system.fs_file, 1024 * 4 , SEEK_SET);
    fwrite(&global_file_system.bitmap, 1024, 1, global_file_system.fs_file);

    /*inode和block一起回写 */

    for (int i = 0; i < NR_INODE; i++)
    {
        if(global_file_system.itable[i] != NULL){
            struct ext2_mem_inode* m_node = global_file_system.itable[i];
            for (int j; j < I_ZONE_SIZE; j++)
            {
                if(m_node->i_zone[j] != 0){
                    // #TODO 2019-07-09 解决这里反复遍历链表而产生的效率问题
                  struct buffer_node* write_back_block = get(m_node->buffer_index, m_node->i_zone[j]);
                  /*这是一个新的数据，在磁盘上还不存在 */
                  if(write_back_block->block == 0){
                      write_back_block->block = get_free_disk_block();
                      m_node->i_d_zone[j] = write_back_block->block;
                  }
                  fseek(global_file_system.fs_file, 1024 * 5 + global_file_system.super_block.s_inodes_count * global_file_system.super_block.s_inode_size + DEFAULT_PER_BLOCK_SIZE * write_back_block->block  , SEEK_SET);
                  fwrite(write_back_block->data, DEFAULT_PER_BLOCK_SIZE, 1, global_file_system.fs_file);
                }
            }
            struct ext2_disk_inode d_node = to_disk(*m_node);
            fseek(global_file_system.fs_file, 1024 * 4 + m_node->i_num * DEFAULT_INODE_SIZE, SEEK_SET);
            fwrite(m_node, DEFAULT_INODE_SIZE, 1, global_file_system.fs_file);
        }
    }
    // /* 回写数据块 */
    // /* 回写数据块的时候要为没有对应盘块的分配新的盘块 */
    // /* 新添加的盘块号要写入inode中，所以要先写回盘块，再写回inode */
    // for (int i = 0; i < NR_BUFFER; i++)
    // {
    //     struct buffer_node *p = global_file_system.btable[i].head;
    //     while (p != NULL)
    //     {
    //         /*如果数据修改过就重新写回 */
    //         if(p->dirt){
    //             if(p->block == 0){
    //                 p->block = get_free_disk_block();
    //             }
    //         }
    //     }
    // }

    // /* 回写inode表 */
    // for (int i = 0; i <NR_INODE; i++)
    // {
    //     if(global_file_system.itable[i] != NULL){
    //         fseek(global_file_system.fs_file,1024 * 5 + sizeof(struct ext2_disk_inode))
    //     }
    // }
    return 1;
}