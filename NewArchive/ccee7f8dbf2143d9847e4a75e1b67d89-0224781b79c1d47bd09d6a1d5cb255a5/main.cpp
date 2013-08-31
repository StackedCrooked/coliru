// http://stackoverflow.com/a/495056/75889
auto foo_hpp = R"hpp(
    template<typename T>
    struct Foo {
        T get();
    };
    
)hpp";

auto foo_cpp = R"cpp(    
    #include "foo.hpp"
    
    template<typename T>
    T Foo<T>::get() {
        return T();
    }
    
    // Explicit instantiations.
    template<> struct Foo<int>;
    template<> struct Foo<char>;    
    
)cpp";

auto test_cpp = R"test_cpp(
    #include "foo.hpp"
    #include <iostream>
    
    int main() {
        std::cout << Foo<int>().get() << std::endl;  // should work?
        std::cout << Foo<char>().get() << std::endl; // should work?
        std::cout << Foo<bool>().get() << std::endl; // should fail?
    }
    
)test_cpp";

#include <fstream>

int main()
{
    std::ofstream("foo.hpp") << foo_hpp;
    std::ofstream("foo.cpp") << foo_cpp;
    std::ofstream("test.cpp") << test_cpp;
}