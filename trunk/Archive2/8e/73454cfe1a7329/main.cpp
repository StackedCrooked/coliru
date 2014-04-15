#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <numeric>
#include <string>
 
int main()
{
    std::vector<std::string> v{"this", "is", "an", "example"};
 
    std::cout << "Old contents of the vector: ";
    for (auto& s : v)
        std::cout << '"' << s << "\" ";
 
    typedef std::vector<std::string>::iterator iter_t;
    std::string concat = std::accumulate(
                             std::move_iterator<iter_t>(v.begin()),
                             std::move_iterator<iter_t>(v.end()),
                             std::string());  // Can be simplified with std::make_move_iterator
 
    std::cout << "\nConcatenated as string: " << concat << '\n'
              << "New contents of the vector: ";
    for (auto& s : v)
        std::cout << '"' << s << "\" ";
    std::cout << '\n';
}