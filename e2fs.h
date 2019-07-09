#ifndef __E2FS_H
#define __E2FS_H

#include "type.h"
#include "node.h"
#include "buffer.h"


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

/* ext2文件系统的整体结构  */
struct ext2_file_system
{
	FILE* fs_file;
	struct ext2_super_block super_block;
	const char* fs_dir;
	int fs_size;
	int grp_count;
	char bitmap[1024];                      /* i节点位图 */
	char blockmap[1024];                    /* 块位图 */
	struct file * fd[NR_OPEN];              /* 系统打开文件表 */
	struct ext2_mem_inode* itable[NR_INODE]; /*系统打开的inode表 */
	struct buffer_head_tail btable[NR_BUFFER];       /* 系统打开的所有块的表 这里的0为无效的 */
};

struct ext2_group_desc
{
	__u32	bg_block_bitmap;      /* 组中块位图所在的块号 */
	__u32	bg_inode_bitmap;      /* 组中索引节点位图所在块的块号 */
	__u32	bg_inode_table;       /*组中索引节点表的首块号 */
	__u16	bg_free_blocks_count; /* 组中空闲块数 */
	__u16	bg_free_inodes_count; /* 组中空闲索引节点数 */
	__u16	bg_used_dirs_count;   /*组中分配给目录的节点数 */
	__u16	bg_pad;               /*填充，对齐到字*/
	__u32   bg_reserved[3];       /*用null填充12个字节*/
};

struct ext2_file_system global_file_system;

/* 申请一个缓冲区 */
int get_buffer();

/*获取空闲的盘块号 */
int get_free_disk_block();

/*获取空闲的inode号 */
int get_free_disk_inode();

/* 获取缓冲链表上的一个缓冲块 */
struct buffer_node* get(int buffer_head, int buffer);

#endif // !2FS_H