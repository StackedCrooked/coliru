#include <iostream>
#include <utility>
#include <string>
 
#include <map>

struct foo {};

int main()
{
    std::map<int, foo> m;
 
    m.emplace(std::pair<int, foo>(1, {}));
    m.emplace(std::piecewise_construct,
              std::forward_as_tuple(2),
              std::forward_as_tuple());
}
