#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int to_int(const char* number){
    int sum = 0;
    for (int i = 0; i < strlen(number); i++)
    {
        sum *= 10;
        sum += number[i] - '0';
    }
    return sum;
}


char *get_1K0(){
    char *_1K = (char*)malloc(1024);
    memset(_1K, 0, 1024);
    return _1K;
}

char *get_1K1(){
    char *_1K = (char*)malloc(1024);
    memset(_1K, -1, 1024);
    return _1K;
}


/**
 * offset, number 以bit为单位
 */
void set_bits(FILE *fp, int offset, int number, char tag){
    // #TODO 2019-07-09 实现set_bits工具类的复杂情况
    /** 先实现简单的情况,offset为8的倍数 */
    char buf[number];
    fseek(fp, offset / 8, SEEK_SET);
    fread(buf, number, 1, fp);
    int size = number / 8;
    int rest_bit =number % 8; // 再设置最后余下的不足一个字节的位
    printf("size: %d rest_bit: %d \n", size, rest_bit);
    memset(buf, tag, size); // 先一个字节一个字节地设置
    char base = 1;
    char target = buf[size]; // 全1
    for (int i = 0; i < rest_bit; i++)
    {
        target = target & (~base);
        base = (1 << base);
    }
    memset(buf + size, target, 1);
    fseek(fp, offset / 8, SEEK_SET);
    fwrite(buf, number, 1, fp);
}

void print_bit(char c){
    int base = 1;
    for (int i = 0; i < 8; i++)
    {
        if((base & c) == 0){
            printf("0");
        }else{
            printf("1");
        }
        base <<= 1;
    }
}