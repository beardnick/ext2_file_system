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


// #TODO 2019-07-08 完成设置bit的工具类
void set_bits(FILE *p, int offset, int number){
}