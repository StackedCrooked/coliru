#include <iostream>

#define B(x) x

#if defined(A) && B(1
#undef D
#define D 2
)
#endif

int main()
{
    std::cout << D << '\n';
}
