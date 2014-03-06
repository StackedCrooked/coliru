#include <iostream>
#include <string>
#include <vector>

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

    uint32_t n  = '20ET';
    auto b = (uint8_t*)(&n);
    std::cout << int(b[0]) << " " << char(b[0]) << std::endl;
    std::cout << int(b[1]) << " " << char(b[1]) << std::endl;
    std::cout << int(b[2]) << " " << char(b[2]) << std::endl;
    std::cout << int(b[3]) << " " << char(b[3]) << std::endl;
//25VL
//25AR
//
//3IP4
//3IC4
//
//3IP6
//3IC6
//
//4TCP
//4UDP

}
