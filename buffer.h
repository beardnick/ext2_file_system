#ifndef __BUFFER_H
#define __BUFFER_H


struct buffer_node
{
    char data[1024]; /*一个逻辑块的数据部分 */
    // struct buffer_node *prev;
    struct buffer_node *next;
    int dirt;        /*是否被修改过 */
    int block;       /*对应的磁盘的盘块号 */
};

struct  buffer_head_tail
{
    struct buffer_node *head;
    struct buffer_node *tail;
};


#endif // !1__BUFFER_H