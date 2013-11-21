#include <map>
#include <string>
#include <algorithm>
#include <iostream>

std::map<std::string, std::map<std::string, int>> grandMap =
    { { "1", { { "hello", 42 }, { "hi", 1337 } } },
      { "2", { { "hello", 42 }, { "hello", 1729 } } }};
          
auto count(std::string const& term)
{
     return std::count_if(std::begin(grandMap), std::end(grandMap),
        [&] (decltype(grandMap)::value_type const& entry)
    {
        return (entry.second.find("hello") != std::end(entry.second));
    });
}

int main()
{
    std::cout << count("hello");
}