#include <iostream>
#include <string>
#include <vector>


typedef std::vector<std::string> Sentence;


std::ostream& operator<<(std::ostream& os, const Sentence & sentence)
{
    for (typename Sentence::const_iterator i = sentence.begin(), e = sentence.end(); i != e; ++i)
    {
        os << (*i) << " ";
    }
    return os;
}


int main()
{
    Sentence sentence = { "Hello", "from", "GCC", __VERSION__, "!" };    
    std::cout << sentence << std::endl;
}
