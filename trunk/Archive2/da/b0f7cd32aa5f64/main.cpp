#include <iostream>
#include <type_traits>

template <typename T>
struct A : T
{    
    template <typename Arg, typename... Args, typename = typename std::enable_if<!std::is_constructible<int, Arg>::value>::type>
    A(Arg&& param, Args&&... params) : T(std::forward<Arg>(param), std::forward<Args>(params)...), x(0) {
        std::cout << "Member 'x' was default constructed\n"; 
    }

    template <typename O, typename... Args, typename = typename std::enable_if<std::is_constructible<int, O>::value>::type>
    A(const O& z, Args&&... params) : T(std::forward<Args>(params)...), x(z) {
        std::cout << "Member 'x' was constructed from arguments\n"; 
    }

    int x;
};

struct B
{
    B(const char*) {}
};

int main()
{
    A<B> a("test");
    A<B> y(3, "test");
}
