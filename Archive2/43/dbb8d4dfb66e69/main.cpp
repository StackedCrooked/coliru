#include <iostream>
#include <functional>
#include <utility>

struct Noisy
{
    Noisy() { std::cout << "Noisy()" << std::endl; }
    Noisy(const Noisy&) { std::cout << "Noisy(const Noisy&)" << std::endl; }
    Noisy(Noisy&&) { std::cout << "Noisy(Noisy&&)" << std::endl; }
    ~Noisy() { std::cout << "~Noisy()" << std::endl; }
    Noisy& operator=(const Noisy&) { std::cout << "operator=(const Noisy&)" << std::endl; return *this; }
    Noisy& operator=(Noisy&&) { std::cout << "operator=(Noisy&&)" << std::endl; return *this; }
};

struct Base
{
    int target(Noisy& a, Noisy b)
    {
        std::cout << "Base::target" << std::endl;
        return 0;
    }
};

Base* get_base() { static Base b; return &b; }

template <typename T, T t>
struct trap;

template <typename R, typename... Args, R(Base::*t)(Args...)>
struct trap<R(Base::*)(Args...), t>
{    
    static R call(Args... args)
    {
        return (get_base()->*t)(args...);
    }
};

int main()
{
    auto f = &trap<decltype(&Base::target), &Base::target>::call;
    Noisy a, b;
    f(a, b);
}
