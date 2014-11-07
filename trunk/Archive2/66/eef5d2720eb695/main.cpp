#include <iostream>
#include <string>
#include <vector>
#include <sstream>

std::string Cpp_PointerToHex(const void* ptr)
{
    std::stringstream ss;
    ss << std::hex << ptr;
    return ss.str();
}

int main()
{
    std::cout << "Hello from gcc version: " << __VERSION__ << std::endl;
    int i = 0;
    auto b = 0.1;
    std::cout << "Converting pointers to hex: " << Cpp_PointerToHex(&i) << ", " << Cpp_PointerToHex(&b) << "\n";
}
