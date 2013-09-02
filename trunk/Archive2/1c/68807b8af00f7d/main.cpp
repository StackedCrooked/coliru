#include <iostream>

void test(int n)
{
    std::cout << (&n) << std::endl;
    if (n == 0) return;
    return test(n - 1);
}

int main()
{
    test(10);
}
