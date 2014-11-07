#include <algorithm>
#include <iostream>

int main()
{
    int a = 15;
    int b = 8;
    int c = 23;
    int res = *std::max(
        {&a, &b, &c},
        [](int* x, int* y)
        {
            return (*x) < (*y) ? x : y;
        }
    );
    std::cout << res << '\n';
}