#include <stdio.h>
#include <string.h>
#include <cstdlib>

int main(int argc, char** argv)
{
    int i=0, n = atoi(argv[1]);
    char* b = (char*)calloc(1,n*2+1);
    for (; i < n/2; i++)
    {
        int a =0;
        int s = n-i, z = i+i+1;
        memset(b, ' ', s);
        memset(b+s, 'Z', z);
        puts(b);
    }
    memset(b, ' ', n*2);
    for (; i < n; i++)
    {
        int a =0;
        int s = n-(i-n/2) - n/2, z = (i-n/2)*2+1;
        memset(b, ' ', s);
        memset(b+s, 'Z', z);
        memset(b+s+n, 'Z', z);
        puts(b);
    }
    return 0;
}