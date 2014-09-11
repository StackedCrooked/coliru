#include <iostream>
#include <cstddef>

template <typename T>
struct is_incomplete
{    
    using one = char;
    using two = long;
            
    template <std::size_t N>
    struct SFINAE {};
    
    template <typename U>
    static constexpr one test(...);
    
    template <typename U>
    static constexpr two test(SFINAE<sizeof(U)>*);

    static constexpr bool value = sizeof(test<T>(nullptr)) == sizeof(one);
};

struct Foo;

struct Bar {};

bool xyz(){return is_incomplete<Foo>::value; }

struct Foo{};

int main()
{
    std::cout << is_incomplete<Foo>::value << std::endl;
    std::cout << xyz() << std::endl;
    std::cout << is_incomplete<Bar>::value << std::endl;
}
