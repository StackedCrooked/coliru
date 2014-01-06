#include <stdio.h>

int main(int argc, char** argv)
{
    int c=10;
    int b=++c+ ++c;
    printf("%d",b);
    return 0;
}
