#include <iostream>
#include <string>
#include <vector>
#include <functional>


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
    std::function<void()>()();
}
