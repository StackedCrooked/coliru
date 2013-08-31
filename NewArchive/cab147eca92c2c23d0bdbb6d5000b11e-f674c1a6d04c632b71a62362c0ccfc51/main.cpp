#include <iostream>
#include <memory>
#include <string>
#include <typeinfo>
#include <cxxabi.h>

std::string demangled(char const* tname) {
    std::unique_ptr<char, void(*)(void*)>
        name{abi::__cxa_demangle(tname, 0, 0, nullptr), std::free};
    return {name.get()};
}

#define THIS_CLASS_NAME() demangled(typeid(*this).name())

namespace foo {
    template <typename T>
    struct bar {
        bar() {
            std::cout << THIS_CLASS_NAME() << '\n';
        }
    };
}

int main() {
    foo::bar<int> b;
}