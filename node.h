#ifndef __NODE_H
#define __NODE_H

#include "type.h"
#include "e2fs.h"

/* 外存索引节点 */
struct ext2_disk_inode
{	
	unsigned short i_mode;				/* 文件类型和属性(rwx位) */
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
	unsigned short i_zone[9];
	/* these are in memory also */		/* 以下是内存中特有的 */
	struct task_struct * i_wait;		/* 等待该i节点的进程 */
	struct task_struct * i_wait2;		/* for pipes */
	unsigned long i_atime;				/* 最后访问时间 */
	unsigned long i_ctime;				/* i节点自身修改时间 */
	unsigned short i_dev;				/* i节点所在的设备号 */
	unsigned short i_num;				/* i节点号 */
	unsigned short i_count;				/* i节点被使用的次数，0表示该i节点空闲 */
	unsigned char i_lock;				/* 锁定标志 */
	unsigned char i_dirt;				/* 已修改(脏)标志 */
	unsigned char i_pipe;				/* 管道标志 */
	unsigned char i_mount;				/* 安装标志 */
	unsigned char i_seek;				/* 搜寻标志(lseek时) */
	unsigned char i_update;				/* 更新标志 */
};

struct m_inode *iget(struct ext2_file_system* fs, int number);

/*所有的inode的操作方式 */
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

struct ext2_mem_inode get_root_inode();

#endif // !1__NODE_H
