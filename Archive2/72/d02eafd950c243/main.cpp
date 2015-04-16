#include <iostream>
#include <cstddef>
#include <stdint.h>
#include <array>

// what I tried:
template<class Mapped, class Indicies>
struct map_call_help;

template<class Mapped, int... indices>
struct map_call_help<Mapped, std::integer_sequence<indices...>>
{
    template<class Callable, class... Args>
    static inline void f(Callable && call, Args && ... args)
    {
        call( Mapped::f<indices>(std::forward<Args>(args)...) ...);
        //                       ^^^^^^^^^^^^^^^^^^^^^^^^^^^      1
        //    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ 2
        // nested expansion fails with parse error / expected ')'
        // inner expansion is: std::forward<Args>(args)...
        // outer expansion is: Mapped::f<indices>(_forwarded_args_)...
    }
}
template<int n, class Mapped, class Callable, class... Args>
inline void map_call(Callable && call, Args && ... args)
{
    map_call_help<Mapped, make_int_seq<n>>::f(
          std::forward<Callable>(call), std::forward<Args>(args)... );
}

struct add
{
    template<int n, class A, class B> static inline auto
    f(const A & a, const B & b) -> decltype(std::get<n>(a)+b)
        { return std::get<n>(a) + b; }
};
template<class... Args> void do_stuff(const Args & ... args)
{ /* do stuff with args */ }
// calls do_stuff(add::f<0>(data,2), add::f<1>(data,1),  add::f<2>(data,1) )
// i.e.  do_stuff(2,4,5)

int main() {
    std::tuple<char,short,int,float,double> data = {1,3,5};
    map_call<3, add>(do_stuff, data, 1);
}