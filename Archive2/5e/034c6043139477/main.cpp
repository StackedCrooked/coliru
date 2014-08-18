#include <iostream>

struct S
{
    S()
    {
        std::cout << __PRETTY_FUNCTION__ << '\n';
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
    
    void foo() const
    {
        std::cout << __PRETTY_FUNCTION__ << '\n';
    }
};

const S f()
{
    S s;
    return s;
}

int main()
{
    S s1 = f();
    s1.foo();
    
    const S s2 = f();
    s2.foo();
    
    return 0;
}
