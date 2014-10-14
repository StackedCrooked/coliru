#include <boost/fusion/container/map.hpp>
#include <boost/fusion/container/generation.hpp>
#include <boost/fusion/include/at_key.hpp>
#include <iostream>

int main() {
    using namespace boost::fusion;
    map<
         pair<struct name_tag, std::string>, 
         pair<struct value_tag, float>
    > var1 = make_map<name_tag, value_tag>("test", 123.0f);

    std::string s1 = at_key<name_tag>(var1);
    float f1       = at_key<value_tag>(var1);
    
    std::cout << "s1: "   << s1 << "\n";
    std::cout << "f1: "   << f1 << "\n";
}