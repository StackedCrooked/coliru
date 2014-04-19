#include <iostream>
#include <type_traits>

struct Foo {
    template<class Type>
    using is_fooable = std::is_base_of<Foo, Type>;
    
    template<typename Type>
    typename std::enable_if<is_fooable<Type>::value, const bool>::type
    operator==(const Type&) const {
        std::cout << "Is base of Foo\n";
        return false;
    }

    template<typename Type>
    typename std::enable_if<!is_fooable<Type>::value, const bool>::type
    operator==(const Type&) const {
        std::cout << "Another class\n";
        return false;
    }
};

struct Bar : public Foo {};

int main() {
    Foo foo;
    Bar bar;
    (foo == bar);
    (foo == 42);
}