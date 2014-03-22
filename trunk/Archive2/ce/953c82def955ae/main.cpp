#include <iostream>
#include <cstring>
#include <string>

int main()
{
    const char string_a[4] = "foo";
    const char string_b[4] = "foo";
    const char * string_c = string_a;
   
    std::cout << std::boolalpha; // for better bool output
    
    std::cout << "string_a == string_b: " << (string_a == string_b) << std::endl;
    std::cout << "string_a == string_c: " << (string_a == string_c) << std::endl;
    std::cout << std::endl;
    std::cout << "strcmp(string_a, string_b): " << (std::strcmp(string_a, string_b) == 0) << std::endl;
    std::cout << "strcmp(string_a, string_c): " << (std::strcmp(string_a, string_c) == 0) << std::endl;
    
    std::cout << "\n";
    
    std::string string_d = "bar";
    std::string string_e = "bar";
    
    std::cout << "The C++ way: string_d == string_e: " << (string_d == string_e);

    return 0;
}