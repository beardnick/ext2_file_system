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
#define FIRST_DATA_BLOCK 1

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

 struct ext2_group_desc
{
	__u32	bg_block_bitmap;	 /* 组中块位图所在的块号 */
	__u32	bg_inode_bitmap;  /* 组中索引节点位图所在块的块号 */
	__u32	bg_inode_table;  /*组中索引节点表的首块号 */
	__u16	bg_free_blocks_count;  /* 组中空闲块数 */
	__u16	bg_free_inodes_count;  /* 组中空闲索引节点数 */
	__u16	bg_used_dirs_count;	/*组中分配给目录的节点数 */
	__u16	bg_pad;  /*填充，对齐到字*/
	__u32［3］ bg_reserved;   /*用null填充12个字节*/
}
 
 /* 外存索引节点 */
 struct ext2_inode {	
    __u16	i_mode; /* 文件类型和访问权限 */
	__u16	i_uid;	/* 文件拥有者标识号*/
	__u32	i_size; /* 以字节计的文件大小 */
	__u32	i_atime; /* 文件的最后一次访问时间 */
	__u32	i_ctime; /* 该节点最后被修改时间 */
	__u32	i_mtime; /* 文件内容的最后修改时间 */
	__u32	i_dtime; /* 文件删除时间 */
	__u16	i_gid;	/* 文件的用户组标志符 */
	__u16	i_links_count; /* 文件的硬链接计数 */
	__u32	i_blocks; /* 文件所占块数（每块以512字节计）*/
	__u32	i_flags; /* 打开文件的方式 */
   union   /*特定操作系统的信息*/
   __u32	i_block[Ext2_N_BLOCKS];  /* 指向数据块的指针数组 */
	__u32	i_version;	  /* 文件的版本号（用于 NFS） */
	__u32	i_file_acl; /*文件访问控制表（已不再使用） */
	__u32	i_dir_acl;	 /*目录 访问控制表（已不再使用）*/
	 __u8	l_i_frag;	 /* 每块中的片数 */
		 __u32   i_faddr;  /* 片的地址 */
 };

/* 目录文件 */
 struct ext2_dir_entry_2
 {
	 __le32 inode;   // 文件入口的inode号，0表示该项未使用
	 __le16 rec_len; // 目录项长度
	 __u8 name_len;  // 文件名包含的字符数
	 __u8 file_type; // 文件类型
	 char name[255]; // 文件名
};   

 
 

char _1M[1024 * 1024] ;

char _1K[1024] ;

struct fs_struct {
	int count;    /* 共享此结构的计数值 */
	unsigned short umask;  /* 文件掩码 */
	struct inode * root, * pwd;  /* 根目录和当前目录inode指针 */
};
struct files_struct {
	int count;    /* 共享该结构的计数值 */
	fd_set close_on_exec; 
	fd_set open_fds;
	struct file * fd[NR_OPEN];
};

struct file {
	mode_t f_mode;  /* 文件的打开模式 */
	loff_t f_pos;  /* 文件的当前读写位置 */
	unsigned short f_flags; /* 文件操作标志 */
	unsigned short f_count; /* 共享该结构体的计数值 */
	unsigned long f_reada, f_ramax, f_raend, f_ralen, f_rawin;
	struct file *f_next, *f_prev; /* 链接前后节点的指针 */
	struct fown_struct f_owner;  /* SIGIO用PID */
	struct inode * f_inode;  /* 指向文件对应的inode */
	struct file_operations * f_op; /* 指向文件操作结构体的指针 */
	unsigned long f_version; /* 文件版本 */
	void *private_data; /* 指向与文件管理模块有关的私有数据的指针 */
};

/* 这里全部用的是函数指针，相当于是使用了类似于Java中的接口的特性 */
struct file_operations {
	int (*lseek) (struct inode *, struct file *, off_t, int);
	int (*read) (struct inode *, struct file *, char *, int);
	int (*write) (struct inode *, struct file *, const char *, int);
	int (*readdir) (struct inode *, struct file *, void *, filldir_t);
	int (*select) (struct inode *, struct file *, int, select_table *);
	int (*ioctl) (struct inode *, struct file *, unsigned int, unsigned long);
	int (*mmap) (struct inode *, struct file *, struct vm_area_struct *);
	int (*open) (struct inode *, struct file *);
	void (*release) (struct inode *, struct file *);
	int (*fsync) (struct inode *, struct file *);
	int (*fasync) (struct inode *, struct file *, int);
	int (*check_media_change) (kdev_t dev);
	int (*revalidate) (kdev_t dev);
};

struct inode_operations {
	struct file_operations * default_file_ops;
	int (*create) (struct inode *,const char *,int,int,struct inode 
**);
	int (*lookup) (struct inode *,const char *,int,struct inode **);
	int (*link) (struct inode *,struct inode *,const char *,int);
	int (*unlink) (struct inode *,const char *,int);
	int (*symlink) (struct inode *,const char *,int,const char *);
	int (*mkdir) (struct inode *,const char *,int,int);
	int (*rmdir) (struct inode *,const char *,int);
	int (*mknod) (struct inode *,const char *,int,int,int);
	int (*rename) (struct inode *,const char *,int,struct inode 
*,const char *,int, int);
	int (*readlink) (struct inode *,char *,int);
	int (*follow_link) (struct inode *,struct inode *,int,int,struct 
inode **);
	int (*readpage) (struct inode *, struct page *);
	int (*writepage) (struct inode *, struct page *);
	int (*bmap) (struct inode *,int);
	void (*truncate) (struct inode *);
	int (*permission) (struct inode *, int);
	int (*smap) (struct inode *,int);
};

struct ext2_file_system
{
	FILE* fs_file;
	struct ext2_super_block super_block;
	const char* fs_dir;
	int fs_size;
	int grp_count;
	char *bitmap[1024];
	char *blockmap[1024];
};


#endif
