#include <stdio.h>

#define PRINT(fmt, ...) printf("%s:%d: "fmt, __FILE__, __LINE__, ##  __VA_ARGS__)

int main()
{
    int somevar = 5;
    printf("%d", somevar);
}