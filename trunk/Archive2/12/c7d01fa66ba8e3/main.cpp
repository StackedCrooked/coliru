#include <stdio.h>

typedef struct
{
    int a;
    int b;
}Point;

typedef struct
{
    int     flag;
    Point   p;
    int     other;
} Things;

int main(void)
{
    Things all;
    Things *pall = &all;

    printf("%p", &all); // prints "0x41ff2728" (correct)
    printf("%p", &all->flag); // prints "0x41ff2728" (correct)

    printf("%p", &all->p); // prints "(nil)"
    printf("%p", (&all->p)); // prints "(nil)"
    printf("%p", all->p); // prints "(nil)"
    printf("%p", (void *)&all->p); // prints "(nil)"
}