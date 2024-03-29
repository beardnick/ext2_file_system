#ifndef __NODE_H
#define __NODE_H

#include "type.h"

#define I_ZONE_SIZE 9

/* 外存索引节点 */
struct ext2_disk_inode
{	
	unsigned int i_mode;				/* 文件类型和属性(rwx位) */
	unsigned short i_uid;				/* 用户id(文件拥有者标识符) */
	unsigned long i_size;				/* 文件大小(字节数) */
	unsigned long i_time;				/* 修改时间(自1970.1.1.:0算起，秒) */
	unsigned char i_gid;				/* 组id(文件拥有者所在的组) */
	unsigned char i_nlinks;				/* 链接数(多少个文件目录项指向该i节点) */
	unsigned short i_zone[9];			/* 直接(0-6)，间接(7)或双重间接(8)逻辑块号 */
										/* zone是区的意思，可译成区段，或逻辑块 */
};


// 定义内存inode节点
struct ext2_mem_inode 
{
    unsigned short i_mode;
	unsigned short i_uid;
	unsigned long i_size;
	unsigned long i_mtime;
	unsigned char i_gid;
	unsigned char i_nlinks;
	unsigned short i_zone[9]; /* i_zone[i] 为0说明不在buffer当中 */
	/* these are in memory also */		/* 以下是内存中特有的 */
	struct task_struct * i_wait;		/* 等待该i节点的进程 */
	struct task_struct * i_wait2;		/* for pipes */
	unsigned long i_atime;				/* 最后访问时间 */
	unsigned long i_ctime;				/* i节点自身修改时间 */
	unsigned short i_dev;				/* i节点所在的设备号 */
	unsigned short i_num;				/* i节点号 inode在磁盘上的编号*/
	unsigned short i_count;				/* i节点被使用的次数，0表示该i节点空闲 */
	unsigned char i_lock;				/* 锁定标志 */
	unsigned char i_dirt;				/* 已修改(脏)标志 */ unsigned char i_pipe;				/* 管道标志 */
	unsigned char i_mount;				/* 安装标志 */
	unsigned char i_seek;				/* 搜寻标志(lseek时) */
	unsigned char i_update;				/* 更新标志 */
	int buffer_index;                   /* inode对应文件在buffer中的索引号 */
	unsigned short i_d_zone[9];         /* i_zone在磁盘上的编号*/
};

struct ext2_mem_inode *iget(int number);

/*所有的inode的操作方式 */
struct inode_operations {
	struct file_operations * default_file_ops;
	int (*create) (struct ext2_mem_inode *,const char *,int,int,struct ext2_mem_inode 
**);
	int (*lookup) (struct ext2_mem_inode *,const char *,int,struct ext2_mem_inode **);
	int (*link) (struct ext2_mem_inode *,struct ext2_mem_inode *,const char *,int);
	int (*unlink) (struct ext2_mem_inode *,const char *,int);
	int (*symlink) (struct ext2_mem_inode *,const char *,int,const char *);
	int (*mkdir) (struct ext2_mem_inode *,const char *,int,int);
	int (*rmdir) (struct ext2_mem_inode *,const char *,int);
	int (*mknod) (struct ext2_mem_inode *,const char *,int,int,int);
	int (*rename) (struct ext2_mem_inode *,const char *,int,struct ext2_mem_inode 
*,const char *,int, int);
	int (*readlink) (struct ext2_mem_inode *,char *,int);
	int (*follow_link) (struct ext2_mem_inode *,struct ext2_mem_inode *,int,int,struct 
ext2_mem_inode **);
	int (*readpage) (struct ext2_mem_inode *, struct page *);
	int (*writepage) (struct ext2_mem_inode *, struct page *);
	int (*bmap) (struct ext2_mem_inode *,int);
	void (*truncate) (struct ext2_mem_inode *);
	int (*permission) (struct ext2_mem_inode *, int);
	int (*smap) (struct ext2_mem_inode *,int);
};

struct ext2_mem_inode* get_root_inode();

struct ext2_disk_inode to_disk(struct ext2_mem_inode m_node);

struct ext2_mem_inode to_mem(struct ext2_disk_inode d_node);

#endif // !1__NODE_H
