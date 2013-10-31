#include <iostream>
#include <utility>
#include <tuple>
using namespace std;


template <size_t K, class R, class F, class Tup>
struct Explode {
    template <class ... Args>
    static R call(F&& func, Tup&& tup, Args&&... args) {
        return Explode<K-1, R, F, Tup>::call(
            forward<F>(func),
            forward<Tup>(tup),
            get<K-1>(forward<Tup>(tup)),
            forward<Args>(args)...);
    }
};

template <class R, class F, class Tup>
struct Explode<0, R, F, Tup> {
    template <class ... Args>
    static R call(F&& func, Tup&& tup, Args&& ... args) {
        return func(forward<Args>(args)...);
    }
};

template <class F, class ... Args>
auto explode(F&& func, tuple<Args...>&& tup) -> typename result_of<F(Args...)>::type
{
    return Explode<sizeof...(Args),
        typename result_of<F(Args...)>::type,
        F,
        tuple<Args...>&&>::call(
            forward<F>(func),
            forward<tuple<Args...>>(tup));
}

template <class F, class ... Args>
auto explode(F&& func, const tuple<Args...>& tup) -> typename result_of<F(Args...)>::type
{
    return Explode<sizeof...(Args),
        typename result_of<F(Args...)>::type,
        F,
        const tuple<Args...>&>::call(
            forward<F>(func),
            tup);
}

int test(int, double) {
    cout << "int, double" << endl;
    return -1;
}

int main()
{
    cout << explode(test, make_tuple(10, 0.1)) << endl;
    tuple<int, double> t{10, 0.2};
    cout << explode(test, t) << endl;
    return 0;
}
