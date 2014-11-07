#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

std::string Cpp_PointerToHex(const void* ptr)
{
    std::stringstream ss;
    ss << std::hex << "0x" << std::setfill('0') << std::internal << std::setw(2*sizeof(ptr)) << uintptr_t(ptr);
    //ss << std::hex << std::showbase << std::setfill('0') << std::internal << std::setw(2*sizeof(ptr) + 2) << uintptr_t(ptr);
    return ss.str();
}

int main()
{
    std::cout << "Hello from gcc version: " << __VERSION__ << std::endl;
    int i = 0;
    auto b = 0.1;
    std::cout << "Converting pointers to hex: " << Cpp_PointerToHex(&i) << ", " << Cpp_PointerToHex(&b) << ", " << Cpp_PointerToHex(nullptr) << "\n";
}
