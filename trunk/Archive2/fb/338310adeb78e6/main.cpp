#include <iostream>
#include <type_traits>

class C
{
private:
    class integral {};
    class floatingpoint {};

    template<typename T>
    using SelectOverload =
        typename std::conditional<
            std::is_integral<T>::value,
            integral,
            typename std::conditional<std::is_floating_point<T>::value,
                floatingpoint,
                void
            >::type
        >::type;

public:
    template<typename T>
    explicit C(T&& value) { init(std::forward<T>(value), SelectOverload<T>()); }

private:    
    template<typename T>
    void init(T&& value, integral) { std::cout << "integral" << std::endl; }
    template<typename T>
    void init(T&& value, floatingpoint) { std::cout << "floating point" << std::endl; }
    
};

int main()
{
    C a(1);
    C b(1.0);
}