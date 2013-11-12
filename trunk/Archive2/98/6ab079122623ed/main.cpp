#include <functional>
#include <iostream>

template<typename Ret, typename... Args>
class Foo
{
private:
    std::function<Ret(Args...)> _func;

public:
    Foo(const std::function<Ret(Args...)>& func):
        _func(func)
    {}
};

template<typename Ret, typename... Args>
auto make_foo(const std::function<Ret(Args...)>& func)
    -> Foo<Ret, Args...>
{
    return { func };
}


int foo(int a)
{
    return a;
}

int main()
{
    auto var = make_foo(&foo);
}
