#include <type_traits>
#include <limits>
#include <iostream>

class A {
 public:
    unsigned int x;
    public:
    template<typename T, typename = typename std::enable_if<std::is_integral<T>::value, void>::type>
    A(T X) : x(X)
    {
        static_assert(!std::numeric_limits<T>::is_signed, "Unsigned values cannot be accepted");
    }
};

int main()
{
    A ok(5u);
    A bad(0xffffffffffffull);
    
    std::cout << std::hex << bad.x << std::endl;
}
