#include <tuple>
#include <iostream>

template<class T>
T f(T v){
    std::cout << v << " ";
    return v;
}

template<unsigned> struct uint_{};

template<unsigned N, class F, class Tup, class... Vs>
void f_all_ltr(uint_<N>, uint_<N>, F sink, Tup&&, Vs... vs){
    sink(vs...);
}

template<unsigned N, unsigned I, class F, class Tup, class... Vs>
void f_all_ltr(uint_<N> n, uint_<I>, F sink, Tup&& tup, Vs... vs){
    f_all_ltr(n, uint_<I+1>{}, sink, std::forward<Tup>(tup), vs..., f(std::get<I>(tup)));
}

template<class F, class... Args>
void f_all_ltr(F sink, Args... args){
    f_all_ltr(uint_<sizeof...(Args)>{}, uint_<0>{}, sink, std::forward_as_tuple(args...));
}

struct sink{
    template<class... Args>
    void operator()(Args...) const{}
};

int main(){
    f_all_ltr(sink{}, 1,2,3,4,5,6);
}