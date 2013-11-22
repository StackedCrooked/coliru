#include <iostream>
#include <typeinfo>
#include <tuple>

template<class T>
T f(){
    std::cout << typeid(T).name() << "\n";
    return T(42.1337);
}

template<class T>
std::tuple<T> eval_reverse(){
    return std::make_tuple(f<T>());
}

template<class T, class T1, class... Ts>
std::tuple<T, T1, Ts...> eval_reverse(){
    auto t1 = eval_reverse<T1, Ts...>();
    auto t2 = std::make_tuple(f<T>());
    return std::tuple_cat(t2, t1);
}

int main(){
    auto t = eval_reverse<bool, int, float>();
    std::cout << std::get<0>(t) << " "
              << std::get<1>(t) << " "
              << std::get<2>(t) << "\n";
}