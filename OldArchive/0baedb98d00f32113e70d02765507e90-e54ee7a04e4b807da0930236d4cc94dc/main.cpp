#include <tuple>
#include <iostream>

template<unsigned... Is> struct seq{ static constexpr unsigned size = sizeof...(Is); };
template<unsigned I, unsigned... Is>
struct gen_seq : gen_seq<I-1, I-1, Is...>{};
template<unsigned... Is>
struct gen_seq<0, Is...> : seq<Is...>{};

namespace aux{
    using swallow = char[];

#define EXPAND(expr) (void)aux::swallow{ ((expr),'\0')... };

template<unsigned... I1, unsigned... I2, class T>
void split_it(seq<I1...> s1, seq<I2...>, T v){
    std::cout << "Pack 1: ";
    EXPAND(std::cout << std::get<I1>(v) << " ");
    std::cout << "\nPack 2: ";
    EXPAND(std::cout << std::get<s1.size + I2>(v) << " ");
}
} // aux::

template<class... Ts>
void split_it(Ts... vs){
    static constexpr unsigned half = sizeof...(Ts) / 2;
    aux::split_it(gen_seq<half>(), gen_seq<sizeof...(Ts) - half>(), std::forward_as_tuple(vs...));
}

int main(){
    split_it(1,2,3, 10,20,30);
}