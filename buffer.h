#ifndef __BUFFER_H
#define __BUFFER_H


struct buffer
{
    char data[1024]; /*一个逻辑块的数据部分 */
    int dirt = 0;    /*是否被修改过 */
    int block;       /*对应的磁盘的盘块号 */
};

#endif // !1__BUFFER_H