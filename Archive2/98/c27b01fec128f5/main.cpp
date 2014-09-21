#include <stdexcept>
#include <type_traits>
#include <boost/variant/static_visitor.hpp>
#include <boost/mpl/unique.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/size.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/function_types/result_type.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/unique.hpp>
#include <boost/function_types/parameter_types.hpp>
#include <boost/mpl/at.hpp>

#include <boost/lexical_cast.hpp>

#include <iostream>

namespace detail {
template<typename T>
struct mem_fn_traits;

template<typename R, typename T, typename... As>
struct mem_fn_traits<R(T::*)(As...) const>
{
    static const unsigned int arity = sizeof...(As);
    using result_type = R;
    template<int I>
    struct argument
    {
        using type = typename boost::mpl::at_c<boost::mpl::vector<As...>, I>::type;    
    };
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
struct callable_visitor<R, C> : C, public boost::static_visitor<R>
{
    using C::operator();

    callable_visitor(C c) : C(c) {}

    template<typename T>
    R operator()(T&&) const
    {
        throw std::runtime_error("Not implemented operation");
    }
};

template<typename R>
struct callable_visitor<R> {};

struct reduce_op
{
    template<typename T1, typename T2>
    struct apply
    {
        static_assert(std::is_same<T1, T2>::value, "Retrun types are not the same");        
        using type = T1;
    };
};

template<typename S>
struct reduce : boost::mpl::fold<
      S
    , typename boost::mpl::front<S>::type
    , reduce_op
    > 
{};

template<typename S>
struct fold_args : boost::mpl::unique<
      S
    , std::is_same<boost::mpl::placeholders::_1, boost::mpl::placeholders::_2>
    >
{};

template<typename... Cs>
auto make_callable_visitor(Cs... cs)
{
    return callable_visitor<typename reduce<boost::mpl::vector<typename boost::function_types::result_type<decltype(&Cs::operator())>::type...>>::type, Cs...>(cs...);
}

} // detail

int main()
{
    auto vis = detail::make_callable_visitor([](double val) -> std::string { return boost::lexical_cast<std::string>(val); },
                                             [](std::string val) -> std::string { return val; });
    std::cout << typeid(decltype(vis)).name() << std::endl;
    
}
