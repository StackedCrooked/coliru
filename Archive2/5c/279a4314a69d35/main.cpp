#include <stdio.h>

int main()
{
    int outcol = 1;
    int tablen = 8;
    for (; outcol < 50; ++outcol) {
        int len = tablen - (outcol % tablen);
        putchar('0' + len);
    }
    return 0;
}
