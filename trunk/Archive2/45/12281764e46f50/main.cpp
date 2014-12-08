#include <iostream>
#include <utility>

template <class, int> struct Vec {};
//Vec is not my class: it takes «int» instead of «size_t». So «int» is used everywhere.

template<class T> void f1(int a1) {
    std::cout << "f1 with " << a1 << " called, " << __PRETTY_FUNCTION__ << std::endl;
}

template<class T> void f2(double a1, int a2) {
    std::cout << "f2 with " << a1 << ", " << a2 << " called, " << __PRETTY_FUNCTION__ << std::endl;
}

template <template <class...> class F, class T, class... Args>
decltype(auto) callWithIndex(int const n, Args &&... args) {
    static constexpr decltype(&F< Vec<T, 1> >::call) table[] = {
        &F< Vec<T, 1> >::call,
        &F< Vec<T, 2> >::call,
        &F< Vec<T, 3> >::call,
        &F< Vec<T, 4> >::call
    };
    return table[n - 1](std::forward<Args>(args)...);
}

template <template <class...> class F, class... Args>
decltype(auto) callWithTypeAndIndex(int const tid, int const n, Args &&... args) {
    static constexpr decltype(callWithIndex<F, unsigned char, Args...>)* table[] = {
        callWithIndex<F, unsigned char , Args...>,
        callWithIndex<F,   signed char , Args...>,
        callWithIndex<F, unsigned short, Args...>,
        callWithIndex<F,   signed short, Args...>,
        callWithIndex<F,            int, Args...>,
        callWithIndex<F,          float, Args...>,
        callWithIndex<F,         double, Args...>
    };
    return table[tid](n, std::forward<Args>(args)...);
}

template <typename T>
struct f1_template
{ static void call(int a1) {f1<T>(a1);} };

template <typename T>
struct f2_template
{ static void call(double a1, int a2) {f2<T>(a1, a2);} };

void f1(int tid, int n, int a1) {
    callWithTypeAndIndex<f1_template>(tid, n, a1);
}

void f2(int tid, int n, double a1, int a2) {
    callWithTypeAndIndex<f2_template>(tid, n, a1, a2);
}

int main()
{
    f1(1, 2, 3);
	f1(2, 0, 3);
}
