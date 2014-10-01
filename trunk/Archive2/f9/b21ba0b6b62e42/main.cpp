#include <functional>
#include <iostream>

template<int N>
struct my_placeholder { static my_placeholder ph; };

template<int N>
my_placeholder<N> my_placeholder<N>::ph;
    
namespace std {
    template<int N>
    struct is_placeholder<::my_placeholder<N>> : std::integral_constant<int, N> { };
}

template<class R, class T, class...Types, class U, int... indices>
std::function<R (Types...)> bind_first(std::function<R (T, Types...)> f, U val, std::integer_sequence<int, indices...> /*seq*/) {
    return std::bind(f, val, my_placeholder<indices+1>::ph...);
}
template<class R, class T, class...Types, class U>
std::function<R (Types...)> bind_first(std::function<R (T, Types...)> f, U val) {
    return bind_first(f, val, std::make_integer_sequence<int, sizeof...(Types)>());
}
    
void foo(double x, double y, double z){
    std::cout << x << ' ' << y << ' ' << z << '\n';
}
    
int main(){
    std::function<void(double, double, double)> f = foo;
    auto t = bind_first(f, 10);
    t(1, 2);
    t(5, 6);
    auto w = bind_first(t, 20);
    w(1024);
    w(3.14);
}