#include <iostream>


template<typename F, typename G> 
struct Compose
{
    Compose(F f, G g) : f(f), g(g) {}
    
    template<typename T>
    auto operator()(T t) -> decltype(f(t))
    {
        return g(f(t));
    }
    
    F f;
    G g;
};

    
template<typename F, typename G>
auto operator&&(F f, G g)
{
    return Compose{};
}

struct increment
{
    int operator()(int n) const
    {
        return n + 1;
    }
};

struct twice
{
    int operator()(int n) const
    {
        return 2 * n;
    }
};


int main()
{
    auto f = increment{} && twice{};
    std::cout << f(1) << std::endl;
}