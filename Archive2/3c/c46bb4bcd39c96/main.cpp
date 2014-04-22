#include <cstdio>

int main()
{
for (int t = 0; t < 33; t++)
{
    int i = t + (t << 1) + 1;

    printf("%d\n", i);
}
}