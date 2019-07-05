#include "init.h"
#include "type.h"
#include <stdio.h>
#include "util.h"
#include <string.h>
#include <time.h>
#include <stdlib.h>

void init_boot_block(FILE* fp){
    char buffer[1024];
    memset(buffer,1,sizeof(buffer));
    // 初始化引导块, 全为0
    fwrite(_1M, 1024, 1, fp);
}


void init_super_block(int grp_size, int grp_count, int group_id, FILE* fp){
    struct ext2_super_block super_block;
    #define init_sb(filed, value) (super_block.filed = value)
    init_sb(s_inodes_count, grp_size / DEFAULT_INDOE_DIVITION * grp_count); /* 每4KB分配一个inode */
    init_sb(s_blocks_count, grp_size * grp_count + 1);     /* 每一个块的大小为1KB */
    init_sb(s_r_blocks_count, DEFAULT_SUPER_USER_REVERVE_SIZE);         /* 为超级用户预留32KB空间 */
    init_sb(s_free_blocks_count, super_block.s_blocks_count);
    init_sb(s_free_inodes_count, super_block.s_inodes_count);
    init_sb(s_blocks_per_group, grp_size);
    init_sb(s_inodes_per_group, grp_size / DEFAULT_INDOE_DIVITION);
    init_sb(s_first_data_block, FIRST_DATA_BLOCK);
    init_sb(s_frags_per_group, 0);
    init_sb(s_mtime, time(NULL));
    init_sb(s_wtime, time(NULL));
    init_sb(s_mnt_count, 1);
    init_sb(s_max_mnt_count, 0); // #TODO 2019-07-04 这个是什么意思
    init_sb(s_magic, EXT2_SUPER_MAGIC);
    init_sb(s_state, EXT2_VALID_FS);
    init_sb(s_errors, EXT2_ERRORS_DEFAULT);
    init_sb(s_lastcheck, time(NULL));
    init_sb(s_checkinterval, 1000); /* 1秒钟检查一次文件系统 */
    init_sb(s_rev_level, 1);
    init_sb(s_def_resgid,1 );
    init_sb(s_def_resuid,1 );
    init_sb(s_first_ino, 1); /* 0 inode表示没有，不存在 */
    init_sb(s_inode_size, DEFAULT_INODE_SIZE);
    init_sb(s_block_group_nr, group_id);
    init_sb(s_feature_compat, 0);
    init_sb(s_feature_incompat, 0);
	init_sb(s_feature_ro_compat, 0);
    // init_sb(s_uuid, ); // #TODO 2019-07-04 UUID怎么生成
    init_sb(s_algorithm_usage_bitmap, 0);
    // init_sb(s_prealloc_blocks);
    // init_sb(s_prealloc_dir_blocks);
    strcpy(super_block.s_volume_name, "myext2");
    strcpy(super_block.s_last_mounted, "/");
    if(fseek(fp, 1024, SEEK_SET) != 0){
        if(ferror(fp)){
            perror("fseek()");
            exit(1);
        }
    }
    printf("fp -> %d\n", ftell(fp));
    fwrite(&super_block, sizeof(struct ext2_super_block), 1, fp);
}

FILE* mkfs(const char* fs_dir , const char* fs_size){
    FILE* fs;
    fs = fopen(fs_dir, "w+");
    // printf("%d\n", to_int(fs_size));
    // 默认全部初始化为0
    // for (int i = 0; i < to_int(fs_size); i++)
    // {
    //     fwrite(_1M, sizeof(_1M), 1, fs);
    // }
    init_boot_block(fs);
    init_super_block(to_int(fs_size) * 1024 , 1, 0, fs);
    return fs;
}