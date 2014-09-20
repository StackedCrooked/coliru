#include <stdexcept>
#include <boost/variant/static_visitor.hpp>
#include <boost/mpl/unique.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/size.hpp>
#include <boost/type_traits/is_same.hpp>

#include <boost/lexical_cast.hpp>

#include <iostream>

namespace detail {
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
struct callable_visitor<R, C> : C, public boost::static_visitor<R>
{
    using C::operator();

    callable_visitor(C c) : C(c) {}

    template<typename T>
    R operator()(T&&) const
    {
        throw std::runtime_error("Not implemented");
    }
};

template<typename R>
struct callable_visitor<R> {};

template<typename... Cs>
struct common_function_types
{
    using result_type = typename boost::mpl::unique<Cs...
      , boost::is_same<boost::mpl::placeholders::_1, boost::mpl::placeholders::_2>
    >::type;
    static_assert(boost::mpl::size<result_type>::value == 1, "Unique");
};

template<typename... Cs>
auto make_callable_visitor(Cs... cs)
{
    return callable_visitor<typename common_function_types<decltype(&Cs::operator())...>::result_type, Cs...>(cs...);
}

} // detail

int main()
{
    auto vis = detail::make_callable_visitor([](double val) -> std::string { return boost::lexical_cast<std::string>(val); },
                                             [](std::string val) -> std::string { return val; });
    std::cout << typeid(decltype(vis)).name() << std::endl;
    
}
