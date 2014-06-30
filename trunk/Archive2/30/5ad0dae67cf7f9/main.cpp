#include <utility>
#include <iostream>

namespace detail
{
template<int I> struct priority : priority<I - 1>{};
template<> struct priority<0>{};

using otherwise = priority<0>;

template<class F, class... Args>
auto try_call(priority<2>, F&& f, Args&&... args)
    -> decltype(f(std::forward<Args>(args)...), void())
{
    std::cout << "f(args...)\n";
    f(std::forward<Args>(args)...);
}

template<class F, class... Args>
auto try_call(priority<1>, F&& f, Args&&...)
    -> decltype(f(), void())
{
    std::cout << "f()\n";
    f();
}

template<class F, class... Args>
void try_call(otherwise, F&&, Args&&...)
{
    std::cout << "nothing\n";
}
} // detail::

template<class F, class... Args>
void call(F&& f, Args&&... args)
{
    detail::try_call(detail::priority<2>(), f, std::forward<Args>(args)...);
}

int main()
{
    call([](int){}, 42);
    call([]{}, 42);
    call([](int*){}, 42);
}