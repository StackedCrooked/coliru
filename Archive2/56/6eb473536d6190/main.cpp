#include <type_traits>

template<int a> struct X { };
template<int b, int c, int d> struct Y { };

template<class T> struct is_x_or_y : std::false_type {};
template<int a> struct is_x_or_y<X<a>> : std::true_type {};
template<int b, int c, int d> struct is_x_or_y<Y<b,c,d>> : std::true_type {};


template<class A, class B, class = std::enable_if_t<is_x_or_y<A>{} && is_x_or_y<B>{}, void>>
void operator+(A a, B b) { }


int main() {
    
    X<1> x;
    Y<2,3,4> y;
    
    x + y;
    y + x;
    // x + 2; // doesn't compile :)
    return 0;
}