#include <iostream>
#include <utility>
#include <tuple>
#include <functional>

template<typename F, typename T> // F may be a std::function, boost::function, or lambda object
auto func(F f, T t)
{
    return [=]()
    {
        return f(t);
    };
}
int main() {
    auto f = func( [](int x){ std::cout << x << "\n"; }, 7 );
    f();
    f();
}
