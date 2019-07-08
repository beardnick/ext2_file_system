#include "namei.h"
#include "type.h"
#include "e2fs.h"
#include "file.h"

/* 通过路径来查找文件 */
struct ext2_mem_inode* namei(const char *filename, struct ext2_mem_inode *root){
    if(root == NULL){
        root = get_root_inode();
    }
    struct ext2_mem_inode *current = root;
    struct ext2_mem_inode *sub;
    int start =0;
    int end;
    // namei("./path/to/file")
    // namei("/path/to/file")
    // namei("path/to/file")
    for (int i = 0; filename[i] != '\0'; i++)
    {
        if(filename[i] == '/'){
            if(i != 0 && start + 1 < i - 1){
                return NULL;
            }
            if(i == 0){
                current = get_root_inode();
            }
            int file_cnt = current->i_size / sizeof(struct ext2_dir_entry);
            for (int j = 0; j < file_cnt; j++)
            {
                
            }
            
        }
    }
    
}
