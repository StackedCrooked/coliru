#include <iostream>
#include <string>
#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto el : vec)
    {
        os << el << ' ';
    }
    return os;
}


typename std::vector<std::string> string_list;

int main()
{
    std::vector<std::string> words = std::vector<std::string>();
    words.push_back("ABC");
    words.push_back("HIJ");
    words.push_back("XYZ");
    
    std::cout << words;
}
