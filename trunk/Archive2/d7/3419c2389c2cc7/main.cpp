#include <iostream>
#include <typeinfo>
#include <vector>
#include <functional>
#include <cmath>
#include <exception>
#include <string>
#include <locale>
#include <complex>
#include <limits>
#include <valarray>
#include <iterator>
#include <utility>

using namespace std;
#if __cplusplus == 201103L
 #include <array>
 #include <future>
 #include <chrono>
 using namespace std::chrono;
#endif

/* --------use this for rvalue exercises --------*/
struct C;
ostream& operator<<(ostream& out, const C& c) { cout << "(" << &c << ")"; return out; }
struct C {
    C() { cout << "c " << *this << endl; }
    C(const C&) { cout << "cc "<< *this << endl; }
#if __cplusplus == 201103L
    C(C&&) { cout << "mc " << *this<< endl; }
#endif
    ~C() { cout << "d " << *this<< endl; }
    C& operator=(const C&) { cout << "ca " << *this<< endl; return *this;}
#if __cplusplus == 201103L    
    C& operator=(C&&) { cout << "ma "<< *this << endl; return *this; }
#endif
};
/* --------------------------------------------- */

// implementation details, users never invoke these directly
namespace detail
{
    template <typename F, typename Tuple, bool Done, int Total, int... N>
    struct call_impl
    {
        call_impl() { cout << "call_impl1" << endl; }
        static void call(F f, Tuple && t)
        {
            cout << "call1" << endl;
            call_impl<F, Tuple, Total == 1 + sizeof...(N), Total, N..., sizeof...(N)>::call(f, std::forward<Tuple>(t));
        }
    };

    template <typename F, typename Tuple, int Total, int... N>
    struct call_impl<F, Tuple, true, Total, N...>
    {
        call_impl() { cout << "call_impl2" << endl; }
        static void call(F f, Tuple && t)
        {
            cout << "call2" << endl;
            f(std::get<N>(std::forward<Tuple>(t))...);
        }
    };
}

// user invokes this
template <typename F, typename Tuple>
void call(F f, Tuple && t)
{
    typedef typename std::decay<Tuple>::type ttype;
    cout << typeid(Tuple).name() << " " << typeid(ttype).name() << endl;
    detail::call_impl<F, Tuple, 0 == std::tuple_size<ttype>::value, std::tuple_size<ttype>::value>::call(f, std::forward<Tuple>(t));
}

#include <cstdio>
int main()
{
    auto t = std::make_tuple("%d, %d, %d\n", 1,2,3);
    call(std::printf, t);
}