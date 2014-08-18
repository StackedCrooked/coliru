#include <iostream>

struct S
{
    S(const std::string& s)
    {
        std::cout << __PRETTY_FUNCTION__ << " : " << s << '\n';
    }
    
    S(const S&)
    {
        std::cout << __PRETTY_FUNCTION__ << '\n';
    }
    
    S(S&&)
    {
        std::cout << __PRETTY_FUNCTION__ << '\n';
    }
    
    S& operator=(S const&)
    {
        std::cout << __PRETTY_FUNCTION__ << '\n';
        return *this;
    }
    
    S& operator=(S&&)
    {
        std::cout << __PRETTY_FUNCTION__ << '\n';
        return *this;
    }
    
    void foo()
    {
        std::cout << __PRETTY_FUNCTION__ << '\n';
    }
};

const S f()
{
    S s("bob");
    return s;
}

int main()
{
    S s = f();
    s.foo();
    return 0;
}
