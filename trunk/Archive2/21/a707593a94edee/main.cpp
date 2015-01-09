#include <iostream>
#include <functional>

void foo(std::function<void(int)> func, int a)
{
    func(a);
}

struct Baz
{ 
    void bar(int a) { std::cout << "bar(int)\n"; }
};

template <typename T, typename... Args>
static void callFooSugar(T* ptr, void(T::*memFun)(int))
{
    foo(std::bind(memFun, ptr, std::placeholders::_1), 123);
}

int main()
{
    Baz MyBaz;
    callFooSugar(&MyBaz, &Baz::bar);
}
