#include <iostream>
#include <functional>

struct Noisy
{
    Noisy() { std::cout << "Noisy()" << std::endl; }
    Noisy(const Noisy&) { std::cout << "Noisy(const Noisy&)" << std::endl; }
    Noisy(Noisy&&) { std::cout << "Noisy(Noisy&&)" << std::endl; }
    ~Noisy() { std::cout << "~Noisy()" << std::endl; }
};

void foo(Noisy n)
{
    std::cout << "foo(Noisy)" << std::endl;
}

int main()
{
    Noisy n;
    std::function<void(Noisy)> f = foo;
    f(n);
}
