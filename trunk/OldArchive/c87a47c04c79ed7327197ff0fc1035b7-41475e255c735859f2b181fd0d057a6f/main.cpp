#include <iostream>
#include <initializer_list>

template <std::size_t... Is>
struct index {};

template <std::size_t N, std::size_t... Is>
struct gen_seq : gen_seq<N - 1, Is...> {};

template <std::size_t... Is>
struct gen_seq<0, Is...> : index<Is...> {};

template <std::size_t N>
void h() { std::cout << N << std::endl; }

template <std::size_t... Is>
void f(index<Is...>)
{
    auto l = { (h<Is>(), 0)... };
    (void)l;
}

void f()
{
    f(gen_seq<5>{});
}

int main()
{
   f();
}