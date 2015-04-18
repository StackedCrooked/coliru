#include <iostream>
using namespace std;
int main() {
    char *hello = "abcdefgh";
    char c = 'c';
    char *str = hello;
    //printf("%s",str);
    char * end = str;
    char tmp;
    if (str) {
        while (*end) {
            ++end;
        }
        --end;
        while (str < end) {
            tmp = *str;
            printf("hello:%s str:%c, end:%c\n", hello, *str, *end);
            *str++ = *end;
            *end-- = tmp;

        }
    }

    return 0;
}