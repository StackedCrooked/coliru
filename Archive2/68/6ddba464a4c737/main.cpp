#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <set>


namespace Detail {

// Overload resolution:
// (1) decltype removes invalid candidates (SFINAE)
// (2) int/long parameter resolves remaining ambiguity

template<typename Container, typename T>
auto find(Container&& container, T&& val, int) -> decltype(container.find(val))
{
    return container.find(val);
}

template<typename Container, typename T>
auto find(Container&& container, T&& val, long) -> decltype(std::find(begin(container), end(container), val))
{
    return std::find(begin(container), end(container), val);
}

} // namespace Detail


// Finds an item in a container.
// Uses `container.find(...)` if available, otherwise `std::find(...)` is used.
template<typename Container, typename T>
auto find(Container&& container, T&& val)
{
    return Detail::find(container, val, int{}); // prefer int overload in case of ambiguity
}


int main()
{    
    std::set<std::string> wordSet = { "abc", "test", "123" };
    std::cout << *find(wordSet, "test") << std::endl;
        
    std::vector<std::string> wordVector = { "abc", "test", "123" };
    std::cout << *find(wordVector, "test") << std::endl;
    
    auto wordArray = { "abc", "test", "123" };
    std::cout << *find(wordArray, "test") << std::endl;
}
