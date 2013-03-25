#include <iostream>
#include <string>
#include <vector>


//using Sentence = std::vector<std::string>;
typedef std::vector<std::string> Sentence;


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
    Sentence sentence = { "Hi", "from", "GCC", __VERSION__, "!" };    
    std::cout << sentence << std::endl;
}
