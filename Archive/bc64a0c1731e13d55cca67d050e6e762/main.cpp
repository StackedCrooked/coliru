#include <cxxabi.h>
#include <cassert>
#include <stdexcept>
#include <memory>
#include <cstdlib>
#include <string>
#include <typeinfo>
 
class bad_mangled_name : public std::runtime_error {
public:
    bad_mangled_name() : std::runtime_error{"bad name"} {}
};
 
std::string demangle(std::string const& name) {
    int status;
    std::unique_ptr<char, decltype(&std::free)> realname{abi::__cxa_demangle(name.c_str(), nullptr, nullptr, &status), &std::free};
    switch (status) {
        case 0: return realname.get();
        case -1: throw std::bad_alloc{};
        case -2: throw bad_mangled_name{};
    }
    
    assert(false && "Unreachable code reached.");
}
 
template<class T>
std::string name_of_type() {
    return demangle(typeid(T).name());
}

#include <iostream>

int main() {
    std::cout << typeid(bad_mangled_name).name() << " vs. " << name_of_type<bad_mangled_name>() << '\n';
}
