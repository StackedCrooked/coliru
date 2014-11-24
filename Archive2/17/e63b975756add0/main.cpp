#include <cstdio>

int main()
{
    char buf[256];
    int i = 1, j =2;
    snprintf(buf, "%d-blah_%d-blah_%N", i, j);
    printf("%s", buf);
    
    return 0;
}