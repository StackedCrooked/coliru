#include <iostream>
#include <string>
#include <vector>
#include <thread>

thread_local int x = 0;

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

int main()
{
    x = 42;
    std::cout << x << '\n';
    std::thread t([] { std::cout << x << '\n'; });
    t.join();
}
