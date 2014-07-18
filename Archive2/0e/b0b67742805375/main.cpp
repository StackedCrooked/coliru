#include <atomic>
struct s { int x; int y; };

#include <iostream>

int main()
{
    std::atomic<s> x;
    std::cout << x.is_lock_free();
}