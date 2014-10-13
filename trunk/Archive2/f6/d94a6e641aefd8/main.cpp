#include <iostream>

template <typename F>
auto wrapper_ (F&& func, int) -> decltype(func())
{
  func ();
}

template <typename F>
void wrapper_ (F func, ...)
{
  func ();
}

template <typename F>
void wrapper (F&& f)
{
    wrapper_(std::forward<F>(f), 0);
}

struct Functor
{
    Functor() {}
    Functor(const Functor&) { std::cout << "Functor(const Functor&)" << std::endl; }
    void operator()() { std::cout << "operator()" << std::endl; }
};

int main()
{
    Functor f;
    wrapper(f);
}
