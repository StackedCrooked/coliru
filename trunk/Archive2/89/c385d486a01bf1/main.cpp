#include <iostream>
#include <string>
#include <algorithm>

int main()
{
    std::string str1 = "Hallo%",
                str2 = "Hallo World!";
    
    // If str1 might be larger than str2, do a conditional swap here
    auto iters = std::mismatch( str1.begin(), str1.end(), str2.begin(), str2.end(), 
                                [] (char lhs, char rhs) {return lhs != '%' && lhs == rhs;});
                                
    if (iters.first == str1.end() || *iters.first == '%') // Success
        std::cout << "HURRAY!";
}
