#include <iostream>
#include <functional>
#include <iterator>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>
 
int main()
{
    std::vector<std::string> words = {"This", "is", "a", "test"};
    std::vector<std::unique_ptr<std::string>> words2;
    words2.emplace_back(new std::string("another"));
    words2.emplace_back(new std::string("test"));
 
    std::vector<std::size_t> lengths;
    std::transform(words.begin(),
                   words.end(),
                   std::back_inserter(lengths),
                   std::mem_fn(&std::string::size)); // uses references to strings
    std::transform(words2.begin(),
                   words2.end(),
                   std::back_inserter(lengths),
                   std::mem_fn(&std::string::size)); // uses unique_ptr to strings
 
    std::cout << "The string lengths are ";
    for(auto n : lengths) std::cout << n << ' ';
    std::cout << '\n';
}