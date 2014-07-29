#include <sstream>
#include <string>
#include <iostream>
#include <type_traits>

// Imagine this part as some kind of cool parser.
// I've thrown out everything for a simpler demonstration.
template<typename T> T get() {}
template<> int get(){ return 5; }
template<> double get(){ return .5; }
template<> char get(){ return 'X'; }
template<> std::string get(){ return "test"; }

struct Config {
    struct proxy {
        // use cool parser to actually read values
        template<typename T>
        explicit operator T(){ return get<T>(); }
    };

    proxy operator[](const std::string &){ return proxy{}; }
};

int main()
{
    auto conf = Config{};

    auto nbr = int( conf["int"] );
    auto dbl = double( conf["dbl"] );
    auto str = std::string( conf["str"] );

    std::cout << nbr << std::endl; // 5
    std::cout << dbl << std::endl; // 0.5
    std::cout << str << std::endl; // 'X'
}
