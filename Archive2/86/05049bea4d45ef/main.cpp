#include <iostream>

const char* a = "foo";

int main()
{
    const char* b = "foo";
    
    std::cout << "a: " << std::hex << (void*)a << std::endl;
    std::cout << "b: " << std::hex << (void*)b << std::endl;
    std::cout << std::boolalpha << (a == b) << std::endl;
    
    return 0;
}