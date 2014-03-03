#include <iostream>

int main()
{
    enum E { YES };
    union { E e ; int i; } u; u.e = YES; std::cout << u.i;
}
