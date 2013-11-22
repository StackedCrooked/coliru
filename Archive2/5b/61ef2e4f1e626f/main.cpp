#include <boost/any.hpp>
#include <map>
#include <iostream>

struct Dog {};
struct Cat{};

int main()
{
    std::map<std::string,boost::any> m;
    m["dog"] = Dog();
    m["cat"] = Cat();
    Dog d (boost::any_cast<Dog>(m["dog"]));
    try {
        Cat c (boost::any_cast<Cat>(m["dog"]));
    } catch (std::exception const& e) {
        std::cerr<<e.what()<<std::endl;
    }
}
