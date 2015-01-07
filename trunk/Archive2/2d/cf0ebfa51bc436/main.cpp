#include <iostream>
#include <functional>
#include <type_traits>
#include <utility>

struct Base
{
    int f53(short, char) { return 123; }
    int f54(short, char, double) { throw 1; }
} base;

Base* get_base(int) { return &base; }

template <typename T, T t>
struct trap;

template <typename R, typename... Args, R(Base::*t)(Args...)>
struct trap<R(Base::*)(Args...), t>
{    
    static R call(int s, Args... args)
    {
        try
        {
            return (get_base(s)->*t)(std::forward<Args>(args)...);
        }
        catch (...)
        {
            return std::is_integral<R>::value ? static_cast<R>(42) : static_cast<R>(3.14); 
        }
    }
};

struct Foo
{
    struct Table
    {
        int(*fp_53)(int, short, char);
        int(*fp_54)(int, short, char, double);
    }* table = new Table;
    
    void load53()
    {
        table->fp_53 = &trap<decltype(&Base::f53), &Base::f53>::call;
    }
    
    void load54()
    { 
        table->fp_54 = &trap<decltype(&Base::f54), &Base::f54>::call;
    }
};

int main()
{
    Foo f{};
    f.load53();
    f.load54();
        
    std::cout << f.table->fp_53(1, 2, 'a') << std::endl;
    std::cout << f.table->fp_54(3, 4, 'b', 2.72) << std::endl;
}
