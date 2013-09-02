#include <iostream>

int test(int n)
{
    std::cout << (&n) << std::endl;
    return (n == 0) ? 0 : test(n - 1);
}

int main()
{
    test(10);
}
