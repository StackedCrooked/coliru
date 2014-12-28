#include <stdio.h>

int hello(const char *name)
{
    printf("Hello %s\n", name);
    return 3;
}

int call(int (*func)(const char*), const char *name)
{
    return func(name);
}

int main()
{
    int res = call(hello, "Voronoi");
    
    printf("Function returned %d\n", res);
    
    return 0;
}
