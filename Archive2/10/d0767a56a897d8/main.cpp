#include <atomic>
#include <iostream>

int main()
{
    std::atomic<int> i{0};
    std::cout << i << '\n';
}
