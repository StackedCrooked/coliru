#include <unordered_map>
#include <iostream>
#include <boost/utility/string_ref.hpp>
#include <boost/unordered_map.hpp>
#include <boost/functional/hash.hpp>

namespace boost
{
    template<>
    struct hash<string_ref> {
        size_t operator()(string_ref const& sr) const {
            return boost::hash<std::string>()(sr.to_string());
        }
    };
}

int main()
{
    std::unordered_map<boost::string_ref, int, boost::hash<boost::string_ref>, std::equal_to<boost::string_ref> > map;

    map.insert(std::make_pair("one",   1));
    map.insert(std::make_pair("two",   2));
    map.insert(std::make_pair("three", 3));
    map.insert(std::make_pair("four",  4));

    char uniq_three[] = "three";
    std::cout << std::boolalpha << uniq_three << " -> " << map[uniq_three] << '\n';
}
