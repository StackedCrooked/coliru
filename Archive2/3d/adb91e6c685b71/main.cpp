#include <iostream>
#include <string>
#include <typeinfo>
#include <utility>
#include <vector>
#include <type_traits>
#include <boost/function_types/result_type.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/variant.hpp>
#include "boost/mpl/at.hpp"
#include <boost/variant/static_visitor.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/mpl/unique.hpp>
#include <boost/type_traits.hpp>
#include <exception>

template<typename T>
struct fn_traits;

template<typename R, typename T, typename... As>
struct fn_traits<R(T::*)(As...) const>
{
    static const unsigned int arity = sizeof...(As);
    using result_type = R;
};

template<typename Callable>
struct lambda_traits 
    : fn_traits<decltype(&Callable::operator())>
{};

template<typename... Ls>
struct common_traits
{
    using result_type = boost::mpl::unique<Ls..., boost::is_same<boost::mpl::placeholders::_1, boost::mpl::placeholders::_2>>;
};

template<typename R, typename... Cs>
struct callable_visitor;

template<typename R, typename C, typename... Cs>
struct callable_visitor<R, C, Cs...> : C, callable_visitor<R, Cs...>
{
    using C::operator();
    using callable_visitor<R, Cs...>::operator();
    
    callable_visitor(C c, Cs... cs)
        : C(c), callable_visitor<R, Cs...>(cs...)
    {}
};

template<typename R, typename C>
struct callable_visitor<R, C> : public boost::static_visitor<R>, C
{
    using C::operator();
    
    callable_visitor(C c)
        : C(c)
    {}
    
    template<typename T>
    R operator()(T&&) const
    {
        throw std::runtime_error("Not implemented");   
    }
};

template<typename R>
struct callable_visitor<R> {};

template<typename... Cs>
auto make_callable_visitor(Cs... cs)
{
    return callable_visitor<std::string, Cs...>(cs...);
}

int main()
{

    boost::variant<double, std::string, std::vector<int>> variant = 666.5;
    auto vis = make_callable_visitor([](double val) -> std::string { return boost::lexical_cast<std::string>(val); },
                                     [](std::string val) -> std::string { return val; });
    std::cout << typeid(decltype(vis)).name() << std::endl;
    
    try
    {
        std::cout << boost::apply_visitor(vis, variant) << std::endl;

        variant = "Ziarenka smaku";
        std::cout << boost::apply_visitor(vis, variant) << std::endl;
        
        variant = std::vector<int>{1, 2, 3};
        std::cout << boost::apply_visitor(vis, variant) << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << std::endl;   
    }
}
