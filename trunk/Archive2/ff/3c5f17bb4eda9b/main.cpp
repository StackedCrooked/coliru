enum class en : int { A, B };

#include <iostream>

int main()
{
    union { en e; int x; } u{};
    u.e = en::B;
    std::cout << u.x;
}