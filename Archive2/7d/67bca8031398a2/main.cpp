#include <iostream>
#include <string>
#include <vector>
#include <sstream>


typedef int u32;

std::string makeStringOfAddresses(u32 const * const begin, u32 const * const end)
{
    std::stringstream ss;
    ss.flags(std::ios::hex | std::ios::showbase);
    for(u32 const * it = begin; it != end; ++it)
    {
        ss << *it << ", ";
    }
    return ss.str();
}

int main()
{
    int numbers[] = {0x1390, 0x1450, 16, 0x1555600};
    std::cout << makeStringOfAddresses(numbers, numbers+4);
}
