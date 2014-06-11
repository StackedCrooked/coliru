#include <iostream>
#include <map>
#include <algorithm>
#include <string>
#include <vector>
#include <iterator>

int main()
{
    std::multimap<std::string, std::string> m{{"Hello", "World"}, {"Bye", "World"}, {"Foo", "Bar"}};
    std::vector<decltype(m)::value_type> vec;
    
    std::copy_if(m.begin(), m.end(), std::back_inserter(vec),
        [](decltype(m)::value_type const& kv) {
            return std::any_of(kv.first.begin(), kv.first.end(), 
                               [](decltype(*kv.first.begin()) c) {return c == 'e';});
        });
    
    for(auto const& v : vec) {
        std::cout << v.first << ": " << v.second << std::endl;
    }
}
