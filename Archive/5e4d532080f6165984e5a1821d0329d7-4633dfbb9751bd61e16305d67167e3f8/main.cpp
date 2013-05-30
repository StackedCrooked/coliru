#include <functional>
#include <utility>
#include <type_traits>

template<unsigned... Is> struct seq{};
template<unsigned I, unsigned... Is>
struct gen_seq : gen_seq<I-1, I-1, Is...>{};
template<unsigned... Is>
struct gen_seq<0, Is...> : seq<Is...>{};

template<unsigned I> struct placeholder{};

namespace std{
template<unsigned I>
struct is_placeholder<::placeholder<I>> : integral_constant<int, I>{};
} // std::

namespace aux{
template<unsigned... Is, class F, class... Ts>
auto easy_bind(seq<Is...>, F&& f, Ts&&... vs){
    return std::bind(std::forward<F>(f), std::forward<Ts>(vs)..., ::placeholder<1 + Is>()...);
}
} // aux::

template<class R, class C, class... FArgs, class... Args>
auto mem_bind(R (C::*ptmf)(FArgs...), Args&&... vs){
    // the +1s for 'this' argument
    static_assert(sizeof...(Args) <= sizeof...(FArgs) + 1, "too many arguments to mem_bind");
    return aux::easy_bind(gen_seq<(sizeof...(FArgs) + 1) - sizeof...(Args)>(), ptmf, std::forward<Args>(vs)...);
}

template<class T, class C, class... Args>
auto mem_bind(T C::*ptmd, Args&&... vs){
    // just 'this' argument
    static_assert(sizeof...(Args) <= 1, "too many arguments to mem_bind");
    return aux::easy_bind(gen_seq<1 - sizeof...(Args)>(), ptmd, std::forward<Args>(vs)...);
}

#include <iostream>

struct X{
    void f(int a, bool b, double c){
        std::cout << a << " " << b << " " << c << "\n";
    }
    int i = 1729;
};

int main(){
    X x;
    mem_bind(&X::f, x)(42, true, 13.37);
    std::cout << mem_bind(&X::i, x)();
}