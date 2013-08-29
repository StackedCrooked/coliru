#include <iostream>
#include <string>
#include <vector>


using Words = std::vector<std::string>;


std::ostream& operator<<(std::ostream& os, const Words & words)
{
    for (const auto & word : words)
    {
        os << word << " ";
    }
    return os;
}


int main()
{
    Words words = { "hello","zhangyuan" };    
    std::cout << words << std::endl;
}
