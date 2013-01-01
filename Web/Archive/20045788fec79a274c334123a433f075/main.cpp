#include <tuple>
#include <functional>
#include <iostream>

template<unsigned> struct N{};

template<typename ...Args>
struct Arguments
{
    Arguments(Args && ...args) : args_{std::forward<Args>(args)...} {}
    
    template<typename F>
    void apply_on(const F & f)
    {
        do_apply_on(f, N<sizeof...(Args)>());
    }
    
    template<typename F>
    void do_apply_on(const F & f, const N<0> &)
    {
        f();
    }
    
    template<typename F>
    void do_apply_on(const F & f, const N<1> &)
    {
        f(std::get<0>(args_));
    }
    
    template<typename F>
    void do_apply_on(const F & f, const N<2> &)
    {
        f(std::get<0>(args_), std::get<1>(args_));
    }
    
    std::tuple<Args...> args_;
};


int main()
{
    Arguments<int, int> arguments(1, 2);
    arguments.apply_on([](int a, int b) { std::cout << a + b; });
}