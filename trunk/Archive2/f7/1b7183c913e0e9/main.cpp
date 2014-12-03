#include <iostream>

class C
{
public:

    template<typename T, typename = typename std::enable_if<std::is_integral<T>::value>::type>
    C(T i) { std::cout << "integral" << std::endl; }
    template<typename T, typename = typename std::enable_if<std::is_floating_point<T>::value>::type, typename ...Args>
    C(T f, Args...) { std::cout << "floating point" << std::endl; }
};

int main()
{
    C a(1);
    C b(1.0);
}