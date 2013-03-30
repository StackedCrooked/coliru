#include <iostream>
#include <string>
#include <vector>


using Sentence = std::vector<std::string>;


std::ostream& operator<<(std::ostream& os, const Sentence & sentence)
{
    for (const auto & word : sentence)
    {
        os << word << " ";
    }
    return os;
}


int main()
{
    Sentence sentence = { "Jello", "to", "GCC", __VERSION__, "?" };    
    std::cout << sentence << std::endl;
}
