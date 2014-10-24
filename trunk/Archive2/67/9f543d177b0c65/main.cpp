#include <iostream>

template <class T>
struct function_impl;

template <class Ret, class... Args>
struct function_impl<Ret(Args...)> // interface
{
    virtual Ret call(Args&&... args) = 0; // rvalues or collaped lvalues
};

template <class T>
struct function;

template <class Ret, class... Args>
struct function<Ret(Args...)>
{    
    // constructors and other stuff skipped for clarity
    
    Ret operator()(Args... args) // by value, like in the signature
    {
        return impl->call(std::forward<Args>(args)...);
    }

    function_impl<Ret(Args...)>* impl;
};

template <class T>
struct function_wrapper;

template <class Ret, class... Args>
struct function_wrapper<Ret(Args...)> : function_impl<Ret(Args...)>
{    
    // constructors and other stuff skipped for clarity
    
    Ret (*f)(Args...);

    virtual Ret call(Args&&... args) override // see && next to Args!
    {
        return f(std::forward<Args>(args)...);
    }
};

struct Noisy
{
    Noisy() { std::cout << "Noisy()" << std::endl; }
    Noisy(const Noisy&) { std::cout << "Noisy(const Noisy&)" << std::endl; }
    Noisy(Noisy&&) { std::cout << "Noisy(Noisy&&)" << std::endl; }
    ~Noisy() { std::cout << "~Noisy()" << std::endl; }
};

void foo(Noisy n)
{
    std::cout << "foo(Noisy)" << std::endl;
}

int main()
{
    function<void(Noisy)> f;
    function_wrapper<void(Noisy)>* wrapper = new function_wrapper<void(Noisy)>{};
    wrapper->f = foo;
    f.impl = wrapper;
    
    Noisy n;    
    f(n);
}
