#include <tr1/tuple>

template<unsigned I> struct int_{};
template<class T, class F>
void tuple_for_each_i(T& t, F f, int_<0>){
  f(std::tr1::get<0>(t));
}

template<class T, class F, unsigned I>
void tuple_for_each_i(T& t, F f, int_<I>){
  tuple_for_each_i(t, f, int_<I-1>());
  f(std::tr1::get<I>(t));
}

template<class T, class F>
void tuple_for_each(T& t, F f){
  tuple_for_each_i(t, f, int_<std::tr1::tuple_size<T>::value-1>());
}

#include <iostream>

struct print{
    template<class T>
    void operator()(T& v){
        std::cout << v << " ";
    }
};

int main(){
    std::tr1::tuple<int, char, char const*, double> t(42, 'o', "hi", 13.37);
    tuple_for_each(t, print());
}