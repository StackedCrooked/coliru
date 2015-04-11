#include <cstdlib>
#include <cstdio>
int main()
{
int *p = (int*)std::malloc(sizeof(int));
int *q = (int*)std::realloc(p, sizeof(int));
*p = 1; // UB access to a pointer that was passed to realloc
*q = 2;
if (p == q) // UB access to a pointer that was passed to realloc
    std::printf("%d %d\n", *p, *q);
}