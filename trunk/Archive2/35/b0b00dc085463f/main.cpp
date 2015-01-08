#include <iostream>
int& f() { static int i = 100; std::cout << i << '\n'; return i; }

int main()
{
    int& r = f();
    r = 101;
    f();
}
