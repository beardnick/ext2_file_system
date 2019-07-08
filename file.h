#ifndef __FILE_H
#define __FILE_H
#include "type.h"

// 定义文件打开后的处理方式
#define O_RDONLY    1   // 只读
#define O_WRONLY    2   // 只写
#define O_RDWR      3   // 读写
#define O_APPEND    4   // 附加写
#define O_CRETAE    5   // 如果不存在则进行创建，配合mode参数
#define O_EXCL      6   // 用于原子操作，配合O_CREATE如果不存在则创建
#define O_TRUNC     7   // 如果只读只写，则长度截为0
#define O_NOCTTY    8   // 不作为控制终端
#define O_NONBLOCK  9   // 非阻塞
#define O_SYNC      10  // 等待磁盘IO完成

/* 文件的读写权限 */
#define S_IRWXU 00700 
#define S_IRUSR 00400
#define S_IWUSR 00200
#define S_IXUSR 00100

#define S_IRWXG 00070
#define S_IRGRP 00040
#define S_IWGRP 00020
#define S_IXGRP 00010

#define S_IRWXO 00007
#define S_IROTH 00004
#define S_IWOTH 00002
#define S_IXOTH 00001

/* 这里全部用的是函数指针，相当于是使用了类似于Java中的接口的特性 */
struct file_operations {
	int (*lseek) (struct inode *, struct file *, __u32, int);
	/**
	 * inode 文件的inode，一般是内存inode
	 */
	int (*read) (struct inode *, struct file *, char *, int);
	int (*write) (struct inode *, struct file *, const char *, int);
	// int (*readdir) (struct inode *, struct file *, void *, filldir_t);
	// int (*select) (struct inode *, struct file *, int, select_table *);
	int (*ioctl) (struct inode *, struct file *, unsigned int, unsigned long);
	int (*mmap) (struct inode *, struct file *, struct vm_area_struct *);
	int (*open) (struct inode *, struct file *);
	void (*release) (struct inode *, struct file *);
	int (*fsync) (struct inode *, struct file *);
	int (*fasync) (struct inode *, struct file *, int);
	// int (*check_media_change) (kdev_t dev);
	// int (*revalidate) (kdev_t dev);
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


/* 一个进程当前的根目录和当前目录信息 */
struct fs_struct {
	int count;    /* 共享此结构的计数值 */
	unsigned short umask;  /* 文件掩码 */
	struct ext2_mem_inode * root, * pwd;  /* 根目录和当前目录inode指针 */
};


/*一个进程打开的所有文件的信息 */
struct files_struct {
	int count;    /* 共享该结构的计数值 */
	// fd_set close_on_exec; 
	// fd_set open_fds;
	struct file * fd[NR_OPEN]; /* 打开的文件指针 */
};

struct file {
	__u32 f_mode;  /* 文件的打开模式 */
	__u32 f_pos;  /* 文件的当前读写位置 */
	unsigned short f_flags; /* 文件操作标志 */
	unsigned short f_count; /* 共享该结构体的计数值 */
	unsigned long f_reada, f_ramax, f_raend, f_ralen, f_rawin;
	struct file *f_next, *f_prev; /* 链接前后节点的指针 */
	// struct fown_struct f_owner;  /* SIGIO用PID */
	struct inode * f_inode;  /* 指向文件对应的inode */
	struct file_operations * f_op; /* 指向文件操作结构体的指针 */
	unsigned long f_version; /* 文件版本 */
	void *private_data; /* 指向与文件管理模块有关的私有数据的指针 */
};

/* 对普通文件的操作，目录文件也当成普通文件来操作 */


struct file* sys_open(const char* filename, int flag, int mode);

// int sys_write(struct file* fp);

// int sys_read();



#endif // !FILE_H