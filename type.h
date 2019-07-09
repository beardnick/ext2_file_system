#ifndef __TYPE_H
#define __TYPE_H

#include <stdio.h>
#define EXT2_SUPER_MAGIC	0xEF53
#define EXT2_VALID_FS 0x0001
#define EXT2_ERRORS_DEFAULT		2
#define DEFAULT_PER_BLOCK_SIZE 1024 
#define DEFAULT_INODE_SIZE 128
#define DEFAULT_SUPER_USER_REVERVE_SIZE 32
#define DEFAULT_INDOE_DIVITION 1
#define FIRST_DATA_BLOCK 1
// #TODO 2019-07-08 NR_OPEN到底是什么
/* 最多可以打开的文件数 */
#define NR_OPEN 256
#define NR_INODE 1024
#define NR_BUFFER 1024
#define Ext2_N_BLOCKS 100

/*特定数据结构重定义 */
typedef unsigned long __u64;
typedef unsigned int __u32;
typedef signed int __s32;
typedef unsigned short int __u16;
typedef signed short int __s16;
typedef unsigned char __u8;
typedef __u16	__le16;
typedef __u32	__le32;
typedef __u64	__le64;
typedef __u16	__be16;
typedef __u32	__be32;
typedef __u64	__be64;


//  struct bitmap
//  {
// 	 char *_map[1024];
//  };

//  struct blockmap
//  {
// 	 char *_map[2014];
//  };

char _1M[1024 * 1024] ;

char _1K[1024] ;


#endif
