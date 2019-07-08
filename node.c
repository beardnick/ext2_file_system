#include "node.h"
#include <stdlib.h>


// #TODO 2019-07-08 提供真正的得到 root 的inode的函数
struct ext2_mem_inode* get_root_inode(){
    struct ext2_mem_inode* root = (struct ext2_mem_inode *) malloc(sizeof(struct ext2_mem_inode));
    return root;
}