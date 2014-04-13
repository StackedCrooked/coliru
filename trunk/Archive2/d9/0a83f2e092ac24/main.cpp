#include <iostream>
#include <vector>
#include <functional>

template<class T, class F, F(T::*f)>
struct delegate;

template<class T, class R, class... Ts, R(T::*f)(Ts...)>
struct delegate<T, R(Ts...), f>
{
    explicit delegate(T* that)
      : that(that)
    {}

    template<class... As>
    R operator()(As&&... as) const
    {
        return (that->*f)(std::forward<As>(as)...);
    }
    
private:
    
    T* that;
};

class A {
public:
    float method1(float a) { return a; }
};

class B {
public:
    float method2(float a) { return a; }
    float anothermethod2(float a) { return a; }
};

class C {
public:
    float method3(float a) { return a; }
};

int main()
{
    std::vector<std::function<float(float)>> MethodsToCall;
    A a;
    B b;
    C c;
    MethodsToCall.push_back(delegate<A, float(float), &A::method1>(&a));
    MethodsToCall.push_back(delegate<B, float(float), &B::method2>(&b));
    MethodsToCall.push_back(delegate<C, float(float), &C::method3>(&c));
    MethodsToCall.push_back(delegate<B, float(float), &B::anothermethod2>(&b));

    for(auto&& F : MethodsToCall )
    {
        std::cout << F(3.5) << std::endl;
    }
    return 0;
}