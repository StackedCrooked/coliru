#include <iostream>
#include <string>
#include <vector>


using Sentence = std::vector<std::string>;


std::ostream& operator<<(std::ostream& os, Sentence & sentence)
{
    for (auto word : sentence)
    {
        os << word << " ";
    }
    return os;
}


int main()
{
    Sentence sentence = { "Hello", "from", "GCC", __VERSION__, "!" };    
    std::cout << sentence << std::endl;
}
