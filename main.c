#include<stdio.h>
#include<string.h>


// 重新定义相关的数据类型
typedef unsigned long __u64;
typedef unsigned int __u32;
typedef signed int __s32;
typedef unsigned short int __u16;
typedef signed short int __s16;
typedef unsigned char __u8;

struct ext2_super_block
 {	__u32	s_inodes_count;	/* 文件系统中索引节点总数 */
	__u32	s_blocks_count;	/*文件系统中总块数 */
	__u32	s_r_blocks_count;	  /* 为超级用户保留的块数 */
	__u32	s_free_blocks_count;	/*文件系统中空闲块总数 */
	__u32	s_free_inodes_count;	/*文件系统中空闲索引节点总数*/
	__u32	s_first_data_block;	/* 文件系统中第一个数据块 */
	__u32	s_log_block_size;	 /* 用于计算逻辑块大小 */
	__s32	s_log_frag_size;	 /* 用于计算片大小 */
	__u32	s_blocks_per_group;	/* 每组中块数 */
	__u32	s_frags_per_group;  /* 每组中片数 */
	__u32	s_inodes_per_group;	/* 每组中索引节点数 */
	__u32	s_mtime;   /*最后一次安装操作的时间 */
	__u32	s_wtime;  /*最后一次对该超级块进行写操作的时间 */
	__u16	s_mnt_count;	/* 安装计数 */
	__s16	s_max_mnt_count;	 /* 最大可安装计数 */
	__u16	s_magic;  /* 用于确定文件系统版本的标志 */
	__u16	s_state;  /* 文件系统的状态*/
	__u16	s_errors;  /* 当检测到有错误时如何处理 */
	__u16	s_minor_rev_level; 	/* 次版本号 */
	__u32	s_lastcheck;	/* 最后一次检测文件系统状态的时间 */
	__u32	s_checkinterval; /* 两次对文件系统状态进行检测的间隔时间 */
	__u32	s_rev_level;	/* 版本号 */
	__u16	s_def_resuid;	 /* 保留块的默认用户标识号 */
	__u16	s_def_resgid;  /* 保留块的默认用户组标识号*/	
__u32   s_first_ino;  /* 第一个非保留的索引节点 */
__u16   s_inode_size;  /* 索引节点的大小 */
  	__u16   s_block_group_nr;  /* 该超级块的块组号 */
  	__u32   s_feature_compat;  /* 兼容特点的位图*/
 	 __u32   s_feature_incompat;  /* 非兼容特点的位图 */
  	__u32   s_feature_ro_compat;  /* 只读兼容特点的位图*/
  	__u8    s_uuid[16];  /* 128位的文件系统标识号*/
 	 char    s_volume_name[16];  /* 卷名 */
 	 char    s_last_mounted[64];  /* 最后一个安装点的路径名 */
  	__u32   s_algorithm_usage_bitmap;  /* 用于压缩*/
  	__u8    s_prealloc_blocks;  /* 预分配的块数*/
  	__u8    s_prealloc_dir_blocks;  /* 给目录预分配的块数 */
 	 __u16   s_padding1;  /* 填充 */
 	 __u32   s_reserved[204];  /* 用null填充块的末尾 */
 };

int to_int(const char* number){
    int sum = 0;
    for (int i = 0; i < strlen(number); i++)
    {
        sum *= 10;
        sum += number[i] - '0';
    }
    return sum;
}

char _1M[1024 * 1024] ;

FILE* mkfs(const char* fs_dir , const char* fs_size){
    FILE* fs;
    fs = fopen(fs_dir, "w+");
    printf("%d\n", to_int(fs_size));
    // 默认全部初始化为0
    // for (int i = 0; i < to_int(fs_size); i++)
    // {
    //     fwrite(_1M, sizeof(_1M), 1, fs);
    // }

    // 初始化引导块, 全为0
    fwrite(_1M, 1024, 1, fs);
    struct ext2_super_block superblock;
    superblock.
    return fs;
}

/**
 * 程序的入口
 * 将磁盘上的一个文件当作一个文件系统来处理
 * 在该文件上进行数据操作，从而使文件系统的内容改变
 * 命令行参数;
 * myext2 <directory of file system> [size of the file system(M)]
 */

int main(int argc, char const *argv[])
{
    FILE *ext2_system;
    if(argc < 2 ){
        printf("Usage: \n\tmyext2 <directory of file system> [size of the file system(M)]");
    }
  if(( ext2_system =  fopen(argv[1], "r+b")) == NULL){
      if(argc < 3 ){
        printf("文件系统文件不存在，如果要创建文件系统文件，请输入文件系统的大小\nUsage: \n\tmyext2 <directory of file system> [size of the file system(M)]");
      }else{
          ext2_system = mkfs(argv[1], argv[2]);
          printf("%p\n", ext2_system);
      }
  }
  //   read_cmd();
  return 0;
}
