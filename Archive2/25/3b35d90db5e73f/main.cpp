#include <type_traits>
#include <string>
#include <cassert>

template<typename T>
struct lambda_traits_helper;

template<typename T, typename Result, typename... Args>
struct lambda_traits_helper<Result(T::*)(Args...) const>
{
    using result_type = Result;
};

template<typename Func>
struct lambda_traits 
    : lambda_traits_helper<decltype(&Func::operator())>
{};

int main()
{
    {
        auto lambda = []{ return 42; };
        assert((std::is_same<int, lambda_traits<decltype(lambda)>::result_type>::value));
    }
    {
        auto lambda = [](int a){ return std::to_string(a); };
        assert((std::is_same<std::string, lambda_traits<decltype(lambda)>::result_type>::value));
    }
}
