#include <iostream>
#include <string>
#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T> & vector)
{
    for (auto && element : vector)
    {
        os << element << " ";
    }
    return os;
}


int main()
{
    std::vector<std::string> sentence = { "Hello", "from", "GCC", __VERSION__, "!" };    
    std::cout << sentence << std::endl;
}
