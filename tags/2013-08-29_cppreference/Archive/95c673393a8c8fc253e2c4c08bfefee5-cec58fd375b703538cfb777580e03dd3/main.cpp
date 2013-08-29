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
    namespace {
        auto int_ = Foo<int>().get();
        auto char_ = Foo<long>().get();
    }
    
)cpp";

auto test_cpp = R"test_cpp(
    #include "foo.hpp"
    #include <iostream>
    
    int main() {
        std::cout << Foo<int>().get() << std::endl;
        std::cout << Foo<long>().get() << std::endl;
        std::cout << "Done." << std::endl;
    }
    
)test_cpp";

#include <fstream>

int main()
{
    std::ofstream("foo.hpp") << foo_hpp;
    std::ofstream("foo.cpp") << foo_cpp;
    std::ofstream("test.cpp") << test_cpp;
}