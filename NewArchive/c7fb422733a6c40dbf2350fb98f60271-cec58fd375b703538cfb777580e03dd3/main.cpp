#include <fstream>

struct file : std::ofstream {
    template<typename String>
    file(const std::string & name, String && str) : std::ofstream(name) {
        *this << std::forward<String>(str);
    }
};


file foo_hpp("foo.hpp", R"(
    template<typename T>
    struct Foo {
        T get();
    };
    
)");

file foo_cpp("foo.cpp", R"(    
    #include "foo.hpp"
    
    template<typename T>
    T Foo<T>::get() {
        return T();
    }
    
    // Explicit instantiations.
    template struct Foo<int>; // without <>!
    template struct Foo<long>; // without <>!
    
)");

file test_cpp("test.cpp", R"(
    #include "foo.hpp"
    #include <iostream>
    
    int main() {
        std::cout << Foo<int>().get() << std::endl;
        std::cout << Foo<long>().get() << std::endl;
        std::cout << "Done." << std::endl;
    }
    
)");



int main() { }