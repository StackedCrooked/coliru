#include <iostream>

int main()
{
    const char* a = "foo";
    const char* b = "foo";
    
    std::cout << std::boolalpha << a == b << std::endl;
    
    return 0;
}