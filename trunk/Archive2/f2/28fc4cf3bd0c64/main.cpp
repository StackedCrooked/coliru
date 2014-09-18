#include <iostream>
#include <string>
#include <typeinfo>
#include <type_traits>
#include <boost/function_types/result_type.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/for_each.hpp>

template<typename T>
struct fn_traits;

template<typename R, typename T, typename... As>
struct fn_traits<R(T::*)(As...) const>
{
    static const unsigned int arity = sizeof...(As);
    using result_type = R;
    using class_type = T;
    using arg_type = boost::mpl::vector<As...>;
};

template<typename Callable>
struct lambda_traits 
    : fn_traits<decltype(&Callable::operator())>
{};

struct printer
{
    template<typename T>
    void operator()(T&&) const
    {
        std::cout << typeid(T).name() << std::endl;
    }
};

template<typename Lambda>
void examine(Lambda&& l)
{
    std::cout << "--> " << typeid(Lambda).name() << std::endl;
    std::cout << "Result: " << typeid(typename lambda_traits<Lambda>::result_type).name() << std::endl;
    std::cout << "Arity:  " << lambda_traits<Lambda>::arity << std::endl;
    boost::mpl::for_each<typename lambda_traits<Lambda>::arg_type>(printer());
}

int main()
{
    examine([](bool a, int b) -> int { return 1; });
    examine([&](){});
}
