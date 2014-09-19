#include <string>
#include <sstream>
#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>

bool compare_words(std::string const& str0, std::string const& str1)
{
    std::stringstream source0(str0);
    
    std::vector<std::string> v(std::istream_iterator<std::string>(source0), std::istream_iterator<std::string>{});
    std::sort(begin(v), end(v));
    
    std::stringstream source1(str1);
    
    std::string str;
    while(source1 >> str)
    {
        if( ! std::binary_search(begin(v), end(v), str)) return false;
    }
    return true;
}

int main()
{
    std::cout << compare_words("california is hot", "hot california is") << "\n";
    std::cout << compare_words("california is hot", "foo bar") << "\n";
}