#include <algorithm>
#include <iostream>

#include <iostream>

template<class T, T> struct proxy;

template <typename T, typename R, typename... Args, R(T::*mf)(Args...)>
struct proxy<R(T::*)(Args...), mf>
{
    proxy(T& host) : m_Host(host) {}
    
    template <typename... CArgs>
    R call(CArgs&&... args)
    {
        std::cout << __PRETTY_FUNCTION__ << '\n';
        return (m_Host.*mf)(std::forward<CArgs>(args)...);
    }
    
private:
    proxy& operator=(const proxy&);
    T& m_Host;
};

class SomeHost
{
public:
    int SomeGetter()
    {
        std::cout << __PRETTY_FUNCTION__ << '\n';
        return 42;
    }
    
    void SomeSetter(int var)
    {
        std::cout << __PRETTY_FUNCTION__ << '\n';
        m_Var = var;
    }
    
private:
    int m_Var;
};

void test()
{
    SomeHost obj;
    proxy<void(SomeHost::*)(int), &SomeHost::SomeSetter> g(obj);
    g.call(5);

    proxy<int(SomeHost::*)(), &SomeHost::SomeGetter> f(obj);
    f.call();
}

int main()
{
    test();
    return 0;
}
