#include <iostream>
#include <sstream>
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

namespace nonstd
{
    // emulate cin
    std::istringstream cin("hello world! goodbye cruel world...");
}
    
int main()
{
    using namespace std;
    using namespace nonstd;
    using nonstd::cin; // pick out cin
    
    std::string word;
    while (cin >> word)
    {
        std::cout << "\nPlease enter a word: " << std::endl;
        cin >> word;
        std::cout << word;
    }
    
}
