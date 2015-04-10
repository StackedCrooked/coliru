#include <iostream>
#include <cstddef>
#include <type_traits>

template <std::size_t num> class BitValue {};

template <typename T> struct GetBitValue {};
template <std::size_t num> struct GetBitValue<BitValue<num>> : std::integral_constant<std::size_t, num> {};

struct Foo
{
    template <typename T>
    bool get()
    {
        std::size_t num = GetBitValue<T>{};
        std::cout << num << std::endl;
        
        return {};
    }
};

int main()
{    
    Foo foo;
    foo.get<BitValue<123>>();
}
