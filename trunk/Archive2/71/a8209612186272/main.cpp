#include <functional>
#include <memory>
#include <iostream>
#include <type_traits>

class Foo
{
public:
    Foo() {}
    void   print() { std::cout << "void Foo::print" << std::endl; }
    int   rprint() { std::cout << "int Foo::rprint(), ( ret = " << -3142 << " )" << std::endl; return -3142; }
    void  pprint(int x) { std::cout << "void Foo::pprint(int x), ( x = " << x << " )" << std::endl; }
    void mpprint(int x, float y) { std::cout << "void Foo::pprint(int x), ( x = " << x << ", y = " << y << " )" << std::endl; }
    int   cprint(int x) { std::cout << "int Foo::cprint(int x), ( x = " << x << " )" << std::endl; return x; }
    int  mcprint(int x, float y) { std::cout << "int Foo::mcprint(int x, float y), ( x = " << x << ", y = " << y << " )" << std::endl; return x; }
};

template<class>
class Callback; /* undefined */

template<class R, class... Args>
class Callback<R(Args...)> {
public:
    typedef std::function<R(Args...)> Type;

    Callback(Type function) : func(function) {}

    template<class C, R (C::*CMethod)(Args...)>
    static Callback from_mem_fn(C * instance) {
        return Callback(
            [=](Args... args) -> R {
                return method_caller<C, CMethod>(instance, args...);
            }
        );
    }
    
    R invoke(Args && ... args) const { return func(std::forward<Args>(args)...); }

private:
    Type        func;

    template<class C, R(C::*CMethod)(Args...)>
    static R method_caller(C* instance, Args ... args) {
        return (instance->*CMethod)(args...);
    }
};

int main() {
    Foo* foo = new Foo();
    auto c1 = Callback<void()          >::from_mem_fn<Foo, &Foo::  print>(foo);
    auto c2 = Callback<int ()          >::from_mem_fn<Foo, &Foo:: rprint>(foo);
    
    auto c3 = Callback<void(int)       >::from_mem_fn<Foo, &Foo:: pprint>(foo);
    auto c4 = Callback<void(int, float)>::from_mem_fn<Foo, &Foo::mpprint>(foo);
    auto c5 = Callback<int (int)       >::from_mem_fn<Foo, &Foo:: cprint>(foo);
    auto c6 = Callback<int (int, float)>::from_mem_fn<Foo, &Foo::mcprint>(foo);
    
    c1.invoke();
    c2.invoke();
    c3.invoke(123);
    c4.invoke(321, 34.0f);
    c5.invoke(321);
    c6.invoke(321, 12.0f);
}