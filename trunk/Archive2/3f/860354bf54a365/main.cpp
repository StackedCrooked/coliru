#include <iostream>
#include <type_traits>

class WillCast {
public:
    explicit operator int () {
       return 1020;
    }
};

class WontCast {
public:
    template <typename U>
    typename std::enable_if<
        std::is_same<U, int>::value, int
    >::type toInteger()
    {
       return 1324;
    }

    template <typename T>
    explicit operator T();
};

template <>
WontCast::operator int()
{
    return 304;
}

int main() {
    std::cout << static_cast<int>(WillCast{}) << "\n";   // ok
    std::cout << WontCast{}.toInteger<int>() << "\n";    // ok
    std::cout << static_cast<int>(WontCast{});
};