#include <iostream>
#include <stdexcept>

struct foo
{
    foo(int n) : n(n), dothrow(false) { std::cout << "constructed " << n << std::endl; }
    foo(foo const& o) : n(o.n), dothrow(o.dothrow) { std::cout << "copied " << o.n << std::endl; }
    ~foo() noexcept(false)
    {
        std::cout << "destructing " << n << std::endl;
        if(dothrow)
        {
            std::cout << "throwing" << std::endl;
            throw std::runtime_error("dtor");
        }
    }
    
    int n;
    bool dothrow;
};

char const* bar_func(foo f)
{
    f.dothrow = true;
    std::cout << "returning from bar_func" << std::endl;
    return "bar_func's value\n";    
}

char const* qux_func(foo f)
{
    f.dothrow = true;
    std::cout << "returning from qux_func" << std::endl;
    return "qux_func's value\n";   
}

int main()
{
    try
    {
        std::cout << bar_func(foo(1)) << qux_func(foo(2)) << std::flush;
    }
    catch(std::exception const& e)
    {
        std::cout << "caught: " << e.what() << std::endl;
    }
}
