#include <iostream>
#include <functional>

// end recursion if no more arguments
void apply(std::function<void()> f, int)
{
    std::cout << __PRETTY_FUNCTION__ << " (" << __LINE__ << ")\n";
    f();
}

template <typename Head, typename ...Tail>
void apply(std::function<void(Head, Tail...)> f, int i) {
    std::cout << __PRETTY_FUNCTION__ << " (" << __LINE__ << ")\n";
    auto g = [=](Tail&& ...args)
    {
        f(i, std::forward<Tail>(args)...);
    };

    apply(std::function<void(Tail...)>{g}, ++i);
}

template <typename ...Tail>
void apply(std::function<void(double, Tail...)> f, int i)
{
    std::cout << __PRETTY_FUNCTION__ << " (" << __LINE__ << ")\n";
    auto g = [=](Tail&& ...args)
    {
        f(777.0, std::forward<Tail>(args)...);
    };

    apply(std::function<void(Tail...)>{g}, ++i);
}

void foo(int a, int b, double c, int d)
{
    std::cout << __PRETTY_FUNCTION__ << " (" << __LINE__ << ")\n";
    std::cout << a << b << c << d << std::endl;
}

int main()
{
    auto f = std::function<void(int, int, double, int)>(foo);
    apply(f, 0);
}
