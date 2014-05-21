#include <algorithm>
#include <iostream>
#include <string>

int main()
{
    std::string source[2][3] = {
        { "a", "b", "c" },
        { "A", "B", "C" }
    };
    
    std::string destination[2][3];
    std::copy(&source[0][0], &source[0][0] + sizeof(source) / sizeof(source[0][0]),
              &destination[0][0]);
              
    std::cout << std::equal(&source[0][0], &source[0][0] + sizeof(source) / sizeof(source[0][0]),
                            &destination[0][0]) << std::endl;
}