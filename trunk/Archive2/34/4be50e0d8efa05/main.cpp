#include <iostream>
#include <typeinfo>

const auto list = [](auto... xs) -> decltype(auto)
{
    return [=](auto f) -> decltype(auto)
    { 
        return f(xs...); 
    };
};

const auto concat = [](auto xs, auto ys) -> decltype(auto)
{
    return xs([ys](auto... x) -> decltype(auto)
    {
        return ys([=](auto... y) -> decltype(auto)
        {
            return list(x..., y...);  
        });
    });
};

namespace detail {
struct ignore_results
{
    template<typename... Tp>
    ignore_results(Tp&&...) 
    {}
};
} // detail

const auto for_each = [](auto f) -> decltype(auto)
{
    return [f](auto xs)
    {
        auto g = [f](auto x){ f(x); return nullptr; };
        xs([g](auto... x)
        {
            detail::ignore_results{g(x)...};
        });
    };  
};

int main(int argc, char* argv[])
{
    auto xs = list(1, "two", 3.5);
    for_each([](auto x){ std::cout << x << std::endl; })(xs);
    for_each([](auto x){ std::cout << typeid(x).name() << std::endl; })(xs);

    return 0;
}
