#include <iostream>
#include <string>
#include <vector>

using namespace std;

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
    const auto abc = [] { return "Hello World"; };
    cout << abc() << endl;
}
