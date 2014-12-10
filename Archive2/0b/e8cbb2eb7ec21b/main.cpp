#include <utility>



struct Foo
{ 
    Foo() {}
    void foo() && {}
    void foo() volatile && {}
    void foo() const && {}
    void foo() const volatile && {}
    
    void foo() & {}
    void foo() volatile & {}
    void foo() const &  {}
    void foo() const volatile & {}
    
    template<class...Ts>
    void foo(Ts&&...) & {}
    template<class...Ts>
    void foo(Ts&&...) volatile & {}
    template<class...Ts>
    void foo(Ts&&...) const &  {}
    template<class...Ts>
    void foo(Ts&&...) const volatile & {}

    template<class...Ts>
    void foo(Ts&&...) && {}
    template<class...Ts>
    void foo(Ts&&...) volatile && {}
    template<class...Ts>
    void foo(Ts&&...) const &&  {}
    template<class...Ts>
    void foo(Ts&&...) const volatile && {}

    template<class...Ts>
    void foo(Ts&&...,...) & {}
    template<class...Ts>
    void foo(Ts&&...,...) volatile & {}
    template<class...Ts>
    void foo(Ts&&...,...) const &  {}
    template<class...Ts>
    void foo(Ts&&...,...) const volatile & {}
    template<class...Ts>
    void foo(Ts&&...,...) && {}
    template<class...Ts>
    void foo(Ts&&...,...) volatile && {}
    template<class...Ts>
    void foo(Ts&&...,...) const &&  {}
    template<class...Ts>
    void foo(Ts&&...,...) const volatile && {}
};


int main()
{
    const volatile Foo foo;
    foo.foo();
    std::move(foo).foo();
}