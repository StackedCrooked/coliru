#include <functional>
#include <utility>
#include <iostream>

template <typename Arg, typename R, typename... Args>
std::function<R(Arg, Args...)> add_ignored_arg(std::function<R(Args...)> f)
{
    return [f] (auto&& /*arg*/, auto&&... args) { return f(std::forward<decltype(args)>(args)...); };
}

struct B {};

void foo()
{
    std::cout << "foo!" << std::endl;
}

void doSomething(std::function<void(B)> callback)
{
    callback(B{});
}

void myDoSomething(std::function<void()> callback0)
{
    doSomething(add_ignored_arg<B>(callback0));
}

int main()
{
    myDoSomething(&foo);
}
