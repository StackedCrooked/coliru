#include <array>
#include <iostream>

std::array<const char*, 4> Get(const char* data)
{
    return { data, nullptr, nullptr, nullptr };
}

int main()
{
    std::cout << "you suck\n";
}