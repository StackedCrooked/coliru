#include <iostream>
#include <thread>



int main()
{
std::cout << std::hex << (~(uint64_t(0)) << 14) << std::endl;
}