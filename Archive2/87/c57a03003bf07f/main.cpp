#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>

template<typename A, typename F>
auto container_algo_each(A algorithm, F f)
{
    return [&](auto& container)
    {
        algorithm(std::begin(container), std::end(container), f);  
        
        return container;
    };
}

template<typename A, typename F>
auto container_algo_inout(A algorithm, F f)
{
    return [=](auto& container) -> decltype(container)&
    {
        algorithm(std::begin(container), std::end(container), 
                  std::begin(container), f);  
        
        return container;
    };
}

template<typename A, typename F>
auto container_algo_prop(A algorithm, F f)
{
    return [=](auto& container)
    {
        return algorithm(std::begin(container), std::end(container), f);  
    };
}

template<typename C, typename F>
auto operator>>=(C& container, F f) -> decltype(f(container))
{
    return f(container);
}

#define template_func(func) [](auto... args){ return func(std::forward<decltype(args)>(args)...); }

#define each(algo, f) container_algo_each(template_func(algo), f)
#define inout(algo, f) container_algo_inout(template_func(algo), f)
#define prop(algo, f) container_algo_prop(template_func(algo), f)

template<typename C>
struct container : public C
{
    using C::C;
    
    template<typename A>
    auto operator()(A algorithm)
    {
        return (*this) >>= algorithm;   
    }
    
    template<typename F>
    auto map(F f)
    {
        return (*this) >>= inout(std::transform, f);   
    }
    
    template<typename F>
    auto foreach(F f)
    {
        return (*this) >>= each(std::for_each, f);   
    }
};

int main()
{
    container<std::vector<std::string>> words = {
        "Hello", "from", "GCC", __VERSION__
    };
    
    words.map([](const auto& x){ return x + "!!!"; })
         .map([](const auto& x){ return "¡¡¡" + x; })
         .foreach([&](const auto& x){ std::cout << x << " "; });
}
