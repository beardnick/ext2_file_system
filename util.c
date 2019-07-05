#include <string.h>
#include <stdlib.h>

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