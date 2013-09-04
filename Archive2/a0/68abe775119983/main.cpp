#include <string>
#include <map>
#include <iostream>

template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::map<T1, T2>& someMap)
{
    os << "{";
    auto it = someMap.begin(), end = someMap.end();
    while(it != end)
    {
        os << "{" << std::to_string((*it).first) << ", " << (*it).second << "}";
        it++;
    }
    os << "}";
    
    return os;
}

int main()
{
    std::map<int, std::string> myMap = { {1, "foo"}, {2, "bar"}, {3, "baz"} };
    std::cout << myMap << std::endl;
    
    return 0;
}