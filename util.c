#include <string.h>

int to_int(const char* number){
    int sum = 0;
    for (int i = 0; i < strlen(number); i++)
    {
        sum *= 10;
        sum += number[i] - '0';
    }
    return sum;
}