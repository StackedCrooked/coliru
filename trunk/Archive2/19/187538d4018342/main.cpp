#include <iostream>
#include <thread>

struct Noisy
{
    Noisy() { std::cout << "Noisy()" << std::endl; }
    Noisy(const Noisy&) { std::cout << "Noisy(const Noisy&)" << std::endl; }
    Noisy(Noisy&&) { std::cout << "Noisy(Noisy&&)" << std::endl; }
    ~Noisy() { std::cout << "~Noisy()" << std::endl; }
    Noisy& operator=(const Noisy&) { std::cout << "operator=(const Noisy&)" << std::endl; return *this; }
    Noisy& operator=(Noisy&&) { std::cout << "operator=(Noisy&&)" << std::endl; return *this; }
};

template <typename F, typename... A>
void interruptible(F&& Function, A&&... Arguments)
{
    std::thread th(
        [](typename std::decay<F>::type&& Function,
           typename std::decay<A>::type&&... Arguments)
        {
            Function(std::move(Arguments)...);
        },
        Function,
        Arguments...
    );
    th.join();
}

void foo(const Noisy& n)
{
    
}

int main()
{
    interruptible(foo, Noisy{});    
}
