#include <iostream>
#include <memory>
#include <type_traits>

#include <cxxabi.h>
std::string demangle(const char* name) {

    int status = -4; // some arbitrary value to eliminate the compiler warning

    // enable c++11 by passing the flag -std=c++11 to g++
    std::unique_ptr<char, void(*)(void*)> res {
        abi::__cxa_demangle(name, NULL, NULL, &status),
        std::free
    };

    return (status==0) ? res.get() : name ;
}

template<typename T>
void print_type()
{
    std::cout << demangle(typeid(T).name()) << "\n";
}


struct return_type_0 {};
struct return_type_1 {};

template<typename T, typename = typename std::enable_if<std::is_integral<T>{}>::type>
return_type_0 func()
{
    struct local {};
    print_type<local>();
    return {};
}

template<typename T, typename = typename std::enable_if< ! std::is_integral<T>{}>::type>
return_type_1 func()
{
    struct local {};
    print_type<local>();
    return {};
}

int main()
{
    func<int>();
    func<double>();
}