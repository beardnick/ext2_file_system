#ifndef __TYPE_H
#define __TYPE_H

#include <stdio.h>
#define EXT2_SUPER_MAGIC	0xEF53
#define EXT2_VALID_FS 0x0001
#define EXT2_ERRORS_DEFAULT		2
#define DEFAULT_PER_BLOCK_SIZE 1
#define DEFAULT_INODE_SIZE 128
#define DEFAULT_SUPER_USER_REVERVE_SIZE 32
#define DEFAULT_INDOE_DIVITION 1
#define FIRST_DATA_BLOCK 8

/*特定数据结构重定义 */
typedef unsigned long __u64;
typedef unsigned int __u32;
typedef signed int __s32;
typedef unsigned short int __u16;
typedef signed short int __s16;
typedef unsigned char __u8;


/*超级块定义 */
struct ext2_super_block
 {	__u32	s_inodes_count;           /* 文件系统中索引节点总数               */
	__u32	s_blocks_count;           /* 文件系统中总块数                     */
	__u32	s_r_blocks_count;         /* 为超级用户保留的块数                 */
	__u32	s_free_blocks_count;      /* 文件系统中空闲块总数                 */
	__u32	s_free_inodes_count;      /* 文件系统中空闲索引节点总数           */
	__u32	s_first_data_block;       /* 文件系统中第一个数据块               */
	__u32	s_log_block_size;         /* 用于计算逻辑块大小                   */
	__s32	s_log_frag_size;          /* 用于计算片大小                       */
	__u32	s_blocks_per_group;       /* 每组中块数                           */
	__u32	s_frags_per_group;        /* 每组中片数                           */
	__u32	s_inodes_per_group;       /* 每组中索引节点数                     */
	__u32	s_mtime;                  /* 最后一次安装操作的时间               */
	__u32	s_wtime;                  /* 最后一次对该超级块进行写操作的时间   */
	__u16	s_mnt_count;              /* 安装计数                             */
	__s16	s_max_mnt_count;          /* 最大可安装计数                       */
	__u16	s_magic;                  /* 用于确定文件系统版本的标志           */
	__u16	s_state;                  /* 文件系统的状态                       */
	__u16	s_errors;                 /* 当检测到有错误时如何处理             */
	__u16	s_minor_rev_level;        /* 次版本号                             */
	__u32	s_lastcheck;              /* 最后一次检测文件系统状态的时间       */
	__u32	s_checkinterval;          /* 两次对文件系统状态进行检测的间隔时间 */
	__u32	s_rev_level;              /* 版本号                               */
	__u16	s_def_resuid;             /* 保留块的默认用户标识号               */
	__u16	s_def_resgid;             /* 保留块的默认用户组标识号             */
	__u32   s_first_ino;              /* 第一个非保留的索引节点               */
    __u16   s_inode_size;             /* 索引节点的大小                       */
	__u16   s_block_group_nr;         /* 该超级块的块组号                     */
  	__u32   s_feature_compat;         /* 兼容特点的位图                       */
	__u32   s_feature_incompat;       /* 非兼容特点的位图                     */
  	__u32   s_feature_ro_compat;      /* 只读兼容特点的位图                   */
  	__u8    s_uuid[16];               /* 128位的文件系统标识号                */
  	__u32   s_algorithm_usage_bitmap; /* 用于压缩                             */
  	__u8    s_prealloc_blocks;        /* 预分配的块数                         */
  	__u8    s_prealloc_dir_blocks;    /* 给目录预分配的块数                   */
 	__u16   s_padding1;               /* 填充                                 */
 	__u32   s_reserved[204];          /* 用null填充块的末尾                   */
 	char    s_volume_name[16];        /* 卷名                                 */
 	char    s_last_mounted[64];       /* 最后一个安装点的路径名               */
 };

 struct bitmap
 {
	 char *_map[1024];
 };

 struct blockmap
 {
	 char *_map[2014];
 };

 struct grp_description
 {
	 /* data */
 };

struct inode_table
{
	/* data */
};

struct 
{
	/* data */
};


 
 
 

char _1M[1024 * 1024] ;

char _1K[1024] ;

struct ext2_file_system
{
	FILE* fs_file;
	struct ext2_super_block super_block;
	const char* fs_dir;
	int fs_size;
	int grp_count;


};

#endif
