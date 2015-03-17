#include <iostream>
#include <utility>
#include <tuple>
#include <typeinfo>

const auto _list = [](auto... xs) -> decltype(auto)
{
    return [=](auto f) -> decltype(auto)
    { 
        return f(xs...); 
    };
};

template<typename... Xs>
struct list
{
    list(Xs&&... xs)
   
};

const auto to_std_tuple = [](auto xs) -> decltype(auto)
{
    return xs([](auto... x) -> decltype(auto)
    { 
        return std::make_tuple(x...); 
    }); 
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

const auto fmap = [](auto f) -> decltype(auto)
{
    return [f](auto xs) -> decltype(auto)
    {
        return xs([f](auto... x) -> decltype(auto)
        {
            return list(f(x)...);  
        });
    };
};

const auto for_each = [](auto f) -> decltype(auto)
{
    return [f](auto xs) -> void
    {
        xs([f](auto... x)
        {
            //static const int dont_care[sizeof...(x)]{ [f](auto y){ f(y); return 0; }(x)... };  
            //(void)dont_care;
            std::make_tuple(f(x)...);
        });
    };
};

int main(int argc, char* argv[])
{
    //auto xs = concat(list("1", 2), list(3.5, "foo", "bar"));
    auto xs = list(1, "2", 3, 4.5);
    auto print = fmap([](auto x){ std::cout << x << std::endl; return x; });
    print(xs);
    //std::cout << typeid(decltype(to_std_tuple(xs))).name() << std::endl;
    
    return 0;
}
