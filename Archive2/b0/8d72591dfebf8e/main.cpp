#include <functional>
#include <iostream>

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

int main()
{
    auto cb = [](int a, int b){ std::cout << a << " " << b << "\n"; };
    auto wrap_cb = wrap(cb);
    wrap_cb(1, 2);
}