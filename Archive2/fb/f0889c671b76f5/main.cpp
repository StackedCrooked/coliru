#include <iostream>

void testfunc(int x, int y)
{
    std::cout << x + y << std::endl;
}
void call(void (*func)(int, int))
{
    (*func)(5, 5);
    (*func)(2, 1);
}
int main()
{
    call(testfunc);
}
