#include "namei.h"
#include "type.h"
#include "e2fs.h"
#include "file.h"
#include "file_dev.h"
#include <stdlib.h>
#include <string.h>
#include "node.h"

int get_subfiles(struct ext2_mem_inode* parent, struct ext2_dir_entry sub_files[]){
           int file_cnt = parent->i_size / sizeof(struct ext2_dir_entry);
            struct file *fp = (struct file *) malloc(sizeof(struct file));
            fp->f_pos = 0;
            sub_files = (struct ext2_dir_entry *) malloc(file_cnt * sizeof(struct ext2_dir_entry));
            char buf[file_cnt];
            file_read(parent, fp, buf, parent->i_size);
            memcpy(sub_files, buf, parent->i_size);
            return 1;
}

/* 通过路径来查找文件 */
struct ext2_mem_inode* namei(const char *filename, struct ext2_mem_inode *root){
    if(root == NULL){
        root = get_root_inode();
    }
    struct ext2_mem_inode *current = root;
    char path[strlen(filename)];
    strcpy(path, filename);
    int path_len = strlen(path);
    int start = 0;
    // namei("./path/to/file")
    // namei("/path/to/file")
    // namei("path/to/file")
    // #TODO 2019-07-09 namei("/")的情况
    for (int i = 0; i < path_len; i++)
    {
        if(path[i] == '/' || path[i] == '\0'){
            if(i != 0 && start + 1 < i - 1){
                return NULL;
            }
            if(i == 0){
                current = get_root_inode();
                start = 1;
                continue;
            }
            path[i] = '\0';
            // struct file *fp = (struct file *) malloc(sizeof(struct file));
            // fp->f_pos = 0;
            // struct ext2_dir_entry sub_files[file_cnt];
            // char buf[file_cnt];
            // file_read(current, fp, buf, current->i_size);
            // memcpy(sub_files, buf, current->i_size);
            int file_cnt = current->i_size / sizeof(struct ext2_dir_entry);
            struct ext2_dir_entry sub_files[file_cnt];
            get_subfiles(current,sub_files);
            printf("path to find:\n%s\n", path + start);
            printf("files:\n");
            for (int j = 0; j < file_cnt; j++)
            {
                    printf("%s\n",sub_files[j].name);
                if(strcmp(sub_files[j].name, path+ start) == 0){
                    current = iget(sub_files[j].inode);
                }
            }
            start = i + 1;
        }
    }
    return current;
}
