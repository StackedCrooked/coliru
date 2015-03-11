#include <iostream>
#include <string>
#include <vector>
#include <thread>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

void    func()
{
    for (int i = 0; i < 10; i++)
        std::cout << "I am alive" << std::endl;
}

int main()
{
    std::thread funcThread(&func);
    funcThread.detach();
    std::cout << "I am alive" << std::endl;
    func();
    return 0;
}
