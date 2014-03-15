#include <iostream>
#include <map>
#include <string>
#include <tuple>


template<typename Comparator>
std::ostream& operator<<(std::ostream& os, const std::map<std::string, std::string, Comparator>& map)
{
    for (auto&& el : map)
    {
        os << el.first << '=' << el.second << ' ';
    }
    return os;
}


struct compare
{
    bool operator()(const std::string& a, const std::string& b) const
    {
        // id < name < _
        return std::make_tuple<bool, bool, std::string const&>(a != "id", a != "name", a) < 
               std::make_tuple<bool, bool, std::string const&>(b != "id", b != "name", b);
    }
};


int main()
{
    std::map<std::string, std::string, compare> attributes  = {
        { "id", "42" },
        { "name", "foo" },
        { "a", "1" },
        { "b", "2" },
        { "c", "3" }
    };
    
    std::cout << attributes << std::endl;
}
