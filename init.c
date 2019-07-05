#include "init.h"
#include "type.h"
#include <stdio.h>
#include "util.h"
#include <string.h>
#include <time.h>
#include <stdlib.h>


struct ext2_file_system mkfs(const char* fs_dir , const char* fs_size){
    struct ext2_file_system fs;
    fs.fs_dir = fs_dir;
    fs.fs_size = to_int(fs_size);
    fs.fs_file = fopen(fs_dir, "w+");
    fs.grp_count = 1;
    init_to_zero(&fs);
    init_boot_block(&fs);
    init_super_block(&fs);
    init_bitmap(&fs);
    init_blockmap(&fs);
    init_grp_description(&fs);
    return fs;
}

void init_to_zero(struct ext2_file_system* fs){
    for (int i = 0; i < fs->fs_size; i++)
    {
        fwrite(_1K, 1024, 1, fs->fs_file);
    }
}

void init_boot_block(struct ext2_file_system* fs){
    char buffer[1024];
    // 初始化引导块, 全为0
    fseek(fs->fs_file, 0, SEEK_SET);
    fwrite(_1K, 1024, 1, fs->fs_file);
}


void init_super_block(struct ext2_file_system* fs){
    #define init_sb(filed, value) (fs->super_block.filed = value)
    init_sb(s_inodes_count, fs->fs_size / DEFAULT_INDOE_DIVITION * fs->grp_count); /* 每1KB分配一个inode */
    init_sb(s_blocks_count,  fs->fs_size / fs->grp_count);     /* 每一个块的大小为1KB */
    init_sb(s_r_blocks_count, DEFAULT_SUPER_USER_REVERVE_SIZE);         /* 为超级用户预留32KB空间 */
    init_sb(s_free_blocks_count, fs->super_block.s_blocks_count);
    init_sb(s_free_inodes_count, fs->super_block.s_inodes_count);
    init_sb(s_blocks_per_group, fs->fs_size / fs->grp_count);
    init_sb(s_inodes_per_group, fs->fs_size / fs->grp_count / DEFAULT_INDOE_DIVITION);
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
    init_sb(s_def_resgid,1);
    init_sb(s_def_resuid,1);
    init_sb(s_first_ino, 1); /* 0 inode表示没有，不存在 */
    init_sb(s_inode_size, DEFAULT_INODE_SIZE);
    init_sb(s_block_group_nr, 0);
    init_sb(s_feature_compat, 0);
    init_sb(s_feature_incompat, 0);
	init_sb(s_feature_ro_compat, 0);
    // init_sb(s_uuid, ); // #TODO 2019-07-04 UUID怎么生成
    init_sb(s_algorithm_usage_bitmap, 0);
    // init_sb(s_prealloc_blocks);
    // init_sb(s_prealloc_dir_blocks);
    strcpy(fs->super_block.s_volume_name, "myext2");
    strcpy(fs->super_block.s_last_mounted, "/");
    if(fseek(fs->fs_file, 1024, SEEK_SET) != 0){
        if(ferror(fs->fs_file)){
            perror("fseek()");
            exit(1);
        }
    }
    printf("fp -> %d\n", ftell(fs->fs_file));
    fwrite(&fs->super_block, sizeof(struct ext2_super_block), 1, fs->fs_file);
}

void init_bitmap(struct ext2_file_system* fs){
    char *_1K = get_1K1();
    /*将s_inodes_count个位设为0 */
    int size = fs->super_block.s_inodes_count / 8; 
    int rest_bit = fs->super_block.s_inodes_count % 8; // 再设置最后余下的不足一个字节的位
    printf("size: %d rest_bit: %d \n", size, rest_bit);
    memset(_1K, 0, size); // 先一个字节一个字节地设置
    char base = 1;
    char target = -1; // 全1
    for (int i = 0; i < rest_bit; i++)
    {
        target = target & (~base);
        base = (1 << base);
    }
    memset(_1K + size, target, 1);
    _1K[0] = 0xFE;
    if(fseek(fs->fs_file, 1024 * 5, SEEK_SET) != 0){
        perror("init_bitmap fseek()");
        exit(1);
    }else{
        printf("fp -> %d\n", ftell(fs->fs_file));
    }
    fwrite(_1K, 1024, 1,fs->fs_file);
    free(_1K);
}

void init_blockmap(struct ext2_file_system* fs){
    char *_1K = get_1K1();
    int size = fs->super_block.s_blocks_count / 8; 
    int rest_bit = fs->super_block.s_blocks_count % 8; // 再设置最后余下的不足一个字节的位
    memset(_1K, 0, size); // 先一个字节一个字节地设置
    char base = 1;
    char target = -1; // 全1
    for (int i = 0; i < rest_bit; i++)
    {
        target = target & (~base);
        base = (1 << base);
    }
    memset(_1K + size, target, 1);
    _1K[0] = 0xFE;
    fseek(fs->fs_file, 1024 * 4, SEEK_SET);
    fwrite(_1K, 1024, 1, fs->fs_file);
    free(_1K);
}

void init_grp_description(struct ext2_file_system* fs){
    fseek(fs->fs_file, 1024 * 3, SEEK_SET);
    fwrite(_1K, 1024, 1, fs->fs_file);
}

void write_origin_data(struct ext2_file_system *fs){

}
