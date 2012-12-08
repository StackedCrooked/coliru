#include <iostream>
#include <type_traits>
using namespace std;

template<bool val, typename True, typename False=void>
struct ternary_op;
template<typename True, typename False>
struct ternary_op<true, True, False> { typedef True type; };
template<typename True, typename False>
struct ternary_op<false, True, False>{ typedef False type; };

template<typename T_> struct target{
    typedef typename ternary_op<std::is_member_object_pointer<T_>::value, T_, T_&>::type T;
};

template<typename T_orig> void f(typename target<T_orig>::T a){
    a=5;
}

template<typename T_orig> void g(typename target<T_orig>::T a){
    a=8;
}

int main() {
    int b=3;
    f<decltype(b)>(b);
    cout<<b<<endl;
    g<decltype(b)>(b);
    cout<<b<<endl;
    return 0;
}