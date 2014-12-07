#include <iostream>


int main() 
{
    for (struct { int a; char b; } i = {1, 'a'}; i.a < 15; ++i.a, ++i.b) 
    {
        printf("%d. %c\n", i.a, i.b);
    }
}