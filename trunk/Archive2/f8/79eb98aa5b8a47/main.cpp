#include <functional>
#include <iostream>

template <typename T>
struct func_traits;

template <typename R>
struct func_traits<R()>
{
    typedef std::function<R()> wrap_type;
};
template <typename R, typename A0>
struct func_traits<R(A0)>
{
    typedef std::function<R(A0)> wrap_type;
};
template <typename R, typename A0, typename A1>
struct func_traits<R(A0, A1)>
{
    typedef std::function<R(A0, A1)> wrap_type;
};
template <typename R, typename A0, typename A1, typename A2>
struct func_traits<R(A0, A1, A2)>
{
    typedef std::function<R(A0, A1, A2)> wrap_type;
};

template <typename R>
struct func_traits<R(*)()> : func_traits<R()> {};
template <typename R, typename A1>
struct func_traits<R(*)(A1)> : func_traits<R(A1)> {};
template <typename R, typename A1, typename A2>
struct func_traits<R(*)(A1, A2)> : func_traits<R(A1, A2)> {};
template <typename R, typename A1, typename A2, typename A3>
struct func_traits<R(*)(A1, A2, A3)> : func_traits<R(A1, A2, A3)> {};
template <typename R, typename C>
struct func_traits<R(C::*)()> : func_traits<R()> {};
template <typename R, typename A1, typename C>
struct func_traits<R(C::*)(A1)> : func_traits<R(A1)> {};
template <typename R, typename A1, typename A2, typename C>
struct func_traits<R(C::*)(A1, A2)> : func_traits<R(A1, A2)> {};
template <typename R, typename A1, typename A2, typename A3, typename C>
struct func_traits<R(C::*)(A1, A2, A3)> : func_traits<R(A1, A2, A3)> {};
template <typename R, typename C>
struct func_traits<R(C::*)() const> : func_traits<R()> {};
template <typename R, typename A1, typename C>
struct func_traits<R(C::*)(A1) const> : func_traits<R(A1)> {};
template <typename R, typename A1, typename A2, typename C>
struct func_traits<R(C::*)(A1, A2) const> : func_traits<R(A1, A2)> {};
template <typename R, typename A1, typename A2, typename A3, typename C>
struct func_traits<R(C::*)(A1, A2, A3) const> : func_traits<R(A1, A2, A3)> {};

template <typename T>
struct func_traits : func_traits<decltype(&T::operator())> {};

template <typename T>
struct func_traits<T&> : func_traits<T> {};
template <typename T>
struct func_traits<T&&> : func_traits<T> {};

void hook()
{
    std::cout << "Called\n";
}

template <typename R>
std::function<R()> wrap(std::function<R()> f)
{
    return [f]()->R { hook(); return f(); };
}

template <typename R, typename T0>
std::function<R(T0)> wrap(std::function<R(T0)> f)
{
    return [f](T0 v0)->R { hook(); return f(v0); };
}

template <typename R, typename T0, typename T1>
std::function<R(T0, T1)> wrap(std::function<R(T0, T1)> f)
{
    return [f](T0 v0, T1 v1)->R { hook(); return f(v0, v1); };
}

template <typename R, typename T0, typename T1, typename T2>
std::function<R(T0, T1, T2)> wrap(std::function<R(T0, T1, T2)> f)
{
    return [f](T0 v0, T1 v1, T2 v2)->R { hook(); return f(v0, v1, v2); };
}

template <typename F>
typename func_traits<F>::wrap_type wrap(F f)
{
    return wrap(typename func_traits<F>::wrap_type(f));
}

int main()
{
    auto cb = std::greater<>;
    auto wrap_cb = wrap(cb);
    wrap_cb(1, 2);
}