#include<stdio.h>
#include<string.h>
#include "init.h"
#include <stdlib.h>
#include "e2fs.h"
#include "file.h"

/**
 * 程序的入口
 * 将磁盘上的一个文件当作一个文件系统来处理
 * 在该文件上进行数据操作，从而使文件系统的内容改变
 * 命令行参数;
 * myext2 <directory of file system> [size of the file system(M)]
 */

// int main(int argc, char const *argv[])
// {
//   struct ext2_file_system fs;
//   // FILE *ext2_system;
//   if (argc < 2)
//   {
//     printf("Usage: \n\tmyext2 <directory of file system> [size of the file system(k)]");
//     exit(1);
//     }
//     if ((fs.fs_file = fopen(argv[1], "r+b")) == NULL)
//     {
//       if(argc < 3 ){
//         printf("文件系统文件不存在，如果要创建文件系统文件，请输入文件系统的大小\nUsage: \n\tmyext2 <directory of file system> [size of the file system(M)]");
//         exit(1);
//       }
//       else
//       {
//         fs = mkfs(argv[1], argv[2]);
//         global_file_system = fs;
//         global_file_system.fs_file = fopen(argv[1], "r+");
//         printf("%p\n", global_file_system.fs_file);
//         create("/", "root", __S_IFDIR);
//         create("/root", "test", __S_IFREG);
//       }
//   }else{
//     printf("加载已存在的文件系统\n");
//   }

//   //   read_cmd();
//   return 0;
// }

int main(int argc, char const *argv[])
{
        struct ext2_file_system fs = mkfs("test.ext2", "32");
        global_file_system = fs;
        // global_file_system.fs_file = fopen("test.ext2", "r+");
        printf("%p\n", global_file_system.fs_file);
        create("/", "root", __S_IFDIR);
        create("/root", "test", __S_IFREG);
  return 0;
}

