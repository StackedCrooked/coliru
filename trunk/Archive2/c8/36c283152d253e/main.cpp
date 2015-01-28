#include <iostream>


// returns the smallest of two values
template<typename T>
const T& Min(const T& a, const T& b)
{
    return a < b ? a : b;
}



int main()
{
    std::cout << Min(1, 2) << std::endl;
    std::cout << Min('a', 'b') << std::endl;
    
    // it also works with strings
    const std::string& result = Min(std::string("abc"), std::string("def"));
    std::cout << result << std::endl;
}

