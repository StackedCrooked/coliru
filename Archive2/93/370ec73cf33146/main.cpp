enum en : int { A, B };

#include <iostream>

int main()
{
    union { en e; int x; } u{};
    u.e = 1;
    std::cout << u.x;
}