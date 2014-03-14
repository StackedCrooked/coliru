#include <iostream>
#include <string>
#include <vector>

void operator delete (void *, float x)
{
    std::cout << "hello there!\n" << x;
}

int
main ()
{
    int x;
    operator delete(&x, 1.25);
}
