#include <iostream>
#include <memory>
#include <string>
#include <typeinfo>
#include <cxxabi.h>

struct malloc_deleter {
    template <typename T>
    void operator ()(T* x) const {
        std::free(x);
    }
};
std::string demangled(char const* tname) {
    std::unique_ptr<char, malloc_deleter> name{abi::__cxa_demangle(tname, 0, 0, nullptr)};
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