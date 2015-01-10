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

struct Foo {};
struct Bar
{
    explicit Bar(const Foo& f) { std::cout << "Bar::Bar(Foo)" << std::endl; }
};

struct Base
{
    void target(Bar, Noisy)
    {
        std::cout << "Base::target" << std::endl;
    }
};

Base* get_base() { static Base b; return &b; }

template <typename T, typename U>
T&& process(U&& u) {
    std::cout << "process(T&&)" << std::endl;
    return std::forward<T>(std::forward<U>(u));
}

template <typename T>
Bar process(Foo x) {
    std::cout << "process(Foo)" << std::endl;
    return Bar{x};
} 

template <typename... Args> // simplified
struct trap
{    
    static void call(Args... args)
    {
        get_base()->target(process<Args>(args)...);
    }
};

int main()
{
    auto f = &trap<Foo, Noisy>::call;
    Foo a;
    Noisy b;
    f(a, b);
}
