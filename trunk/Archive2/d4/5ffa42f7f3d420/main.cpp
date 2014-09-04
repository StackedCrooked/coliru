#include <iostream>

int main()
{
    const char* a = "foo";
    const char* b = "foo";
    
    std::cout << "a: " << std::hex << (void*)a << std::endl;
    std::cout << "b: " << std::hex << (void*)b << std::endl;
    std::cout << std::boolalpha << (a == b) << std::endl;
    
    return 0;
}