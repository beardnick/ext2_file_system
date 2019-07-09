#include "e2fs.h"
#include "buffer.h"
#include <stdlib.h>
#include "type.h"

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

int get_free_disk(){

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
    
    /* 回写数据块 */
    /* 回写数据块的时候要为没有对应盘块的分配新的盘块 */
    /* 新添加的盘块号要写入inode中，所以要先写回盘块，再写回inode */
    for (int i = 0; i < NR_BUFFER; i++)
    {
        struct buffer_node *p = global_file_system.btable[i].head;
        while (p != NULL)
        {
            if(p->dirt)
        }
        
    }

    // /* 回写inode表 */
    // for (int i = 0; i <NR_INODE; i++)
    // {
    //     if(global_file_system.itable[i] != NULL){
    //         fseek(global_file_system.fs_file,1024 * 5 + sizeof(struct ext2_disk_inode))
    //     }
    // }
}