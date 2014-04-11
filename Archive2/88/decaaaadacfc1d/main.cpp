#include <iostream>
#include <vector>

template <size_t... Ns> struct int_seq{ };
template <size_t... Ns> struct make_int_seq;
template <size_t N, size_t... Ns> struct make_int_seq<N, Ns...>
                                              : make_int_seq<N - 1, N, Ns...>{ };
template <size_t... Ns> struct make_int_seq<0, Ns...>
{ using type = int_seq<0, Ns...>; };

template <size_t... Ns>
void show(int_seq<Ns...> const &seq)
{ (std::cout << Ns << " ")...; }

int main() 
{
    auto seq(make_int_seq<10>::type{});
    show(seq);
}
