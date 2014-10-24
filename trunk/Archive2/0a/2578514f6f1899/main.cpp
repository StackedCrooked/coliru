#include <iostream>
#include <utility>

struct Noisy
{
    Noisy() { std::cout << "Noisy()" << std::endl; }
    Noisy(const Noisy&) { std::cout << "Noisy(const Noisy&)" << std::endl; }
    Noisy(Noisy&&) { std::cout << "Noisy(Noisy&&)" << std::endl; }
    ~Noisy() { std::cout << "~Noisy()" << std::endl; }
};

void target(Noisy n) { }  // real function stored in std::function

void delegate3(Noisy&& n) { target(std::forward<Noisy>(n)); }  // internal delegate3
void delegate2(Noisy&& n) { delegate3(std::forward<Noisy>(n)); }  // internal delegate2
void delegate1(Noisy&& n) { delegate2(std::forward<Noisy>(n)); }  // internal delegate1

void source(Noisy n) { delegate1(std::forward<Noisy>(n));  }  // std::function

int main()
{
    Noisy n;
    source(n);
}
