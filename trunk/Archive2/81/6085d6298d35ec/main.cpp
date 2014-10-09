#include <stdio.h>

void b()
{
    printf("b1");
    //do some stuff
    printf("b2");
}
void a()
{
    printf("a1");
    b();
    printf("a2");
}

int main()
{
    a();
}
