#include <iostream>
#include <utility>
#include <functional>


#define TRACE() std::cout << __FILE__ << ":" << __LINE__ << ": " << __PRETTY_FUNCTION__ << std::endl


template<typename T>
struct Lazy
{
    template<typename F>
    Lazy(F&& f) : f(std::forward<F>(f))
    {
        TRACE();
    }
    
    const T* operator->() const
    {
        TRACE();
        if (!t) t = f();
        return t;
    }
    
    T* operator->()
    {
        TRACE();
        return const_cast<T*>(static_cast<const Lazy<T>&>(*this).operator->());
    }
    
private:
    std::function<T*()> f;
    mutable T* t;
};


struct Session
{
    Session() { TRACE(); }
    void foo() { TRACE(); }
};


struct Impl
{
    Impl() : mSession([this] { TRACE(); return new Session(); })
    {
        TRACE();
    }
    
    void test()
    {
        TRACE();
        mSession->foo();
    }
    
    Lazy<Session> mSession;
};



int main()
{
    Impl impl;
    impl.test();
}




