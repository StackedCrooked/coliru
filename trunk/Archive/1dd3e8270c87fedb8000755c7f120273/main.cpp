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
#include <memory>
#include <vector>

int main() {
    std::cout << typeid(std::unique_ptr<std::vector<int>>).name() << " vs. " << name_of_type<std::unique_ptr<std::vector<int>>>() << '\n';
}
