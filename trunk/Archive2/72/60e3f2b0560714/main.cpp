#include <iostream>
#include <cstddef>
#include <stdint.h>
#include <array>
#include <utility>
#include <tuple>
// what I tried:
template<class Mapped>
struct map_call_help {
    template<size_t...indices, class Callable, class... Args>
    void operator()(std::index_sequence<indices...>, Callable&& call, Args&&... args) const
    {
        call( Mapped::template f<indices>(std::forward<Args>(args)...) ...);
        //                       ^^^^^^^^^^^^^^^^^^^^^^^^^^^      1
        //    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ 2
        // nested expansion fails with parse error / expected ')'
        // inner expansion is: std::forward<Args>(args)...
        // outer expansion is: Mapped::f<indices>(_forwarded_args_)...
    }
};
template<int n, class Mapped, class Callable, class... Args>
inline void map_call(Callable && call, Args && ... args)
{
    map_call_help<Mapped>{}(
      std::index_sequence_for<Args...>{},
      std::forward<Callable>(call),
      std::forward<Args>(args)...
    );
}

struct add
{
    template<int n, class A, class B> static inline auto
    f(const A & a, const B & b) -> decltype(std::get<n>(a)+b)
        { return std::get<n>(a) + b; }
};
struct do_stuff {
template<class... Args> void operator()(const Args & ... args)const
{
    using discard=int[];
    (void)discard{0,((
        std::cout << args << '\n'
    ),void(),0)...}; }
};
// calls do_stuff(add::f<0>(data,2), add::f<1>(data,1),  add::f<2>(data,1) )
// i.e.  do_stuff(2,4,5)

int main() {
    std::tuple<char,short,int> data(1,3,5);
    map_call<3, add>(do_stuff{}, data, 1);
}