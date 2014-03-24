#include <iostream>
#include <cstring>
#include <string>

int main()
{
    const char carr_1[4] = "foo";
    const char carr_2[4] = "foo";
    const char * cptr = carr_1;
   
    std::cout << std::boolalpha; // for better bool output
    
    std::cout << "carr_1 == carr_2: " << (carr_1 == carr_2) << std::endl;
    std::cout << "carr_1 == cptr: " << (carr_1 == cptr) << std::endl;
    std::cout << std::endl;
    std::cout << "strcmp(carr_1, carr_2): " << (std::strcmp(carr_1, carr_2) == 0) << std::endl;
    std::cout << "strcmp(carr_1, cptr): " << (std::strcmp(carr_1, cptr) == 0) << std::endl;
    
    std::cout << "\n";
    
    std::string string_1 = "foo";
    std::string string_2 = "foo";
    
    std::cout << "The C++ way: string_1 == string_2: " << (string_1 == string_2);

    return 0;
}