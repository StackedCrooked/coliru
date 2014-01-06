#include <array>
#include <iostream>

std::array<const char*, 4> Get(const char* data)
{
    return { data, nullptr, nullptr, nullptr };
}

std::array<const char*, 4> Get2(const char* data)
{
    return {{ data, nullptr, nullptr, nullptr }};
}

std::array<const char*, 4> Get3(const char* data)
{
    return std::array<const char*, 4>{ data, nullptr, nullptr, nullptr };
}

std::array<const char*, 4> Get4(const char* data)
{
    
    return std::make_array( data, nullptr, nullptr, nullptr );
}

int main()
{
    std::cout << "you suck\n";
}