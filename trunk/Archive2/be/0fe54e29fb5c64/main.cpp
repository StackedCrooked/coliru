#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "inline_visitor_test"
#include <stdexcept>
#include <type_traits>
#include <utility>
#include <boost/lexical_cast.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/is_sequence.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/unique.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/variant.hpp>
#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>

namespace detail {
template<typename T>
struct mem_fn_traits;

template<typename R, typename T, typename... As>
struct mem_fn_traits<R(T::*)(As...) const> {
    using result_type = R;

    template<int I>
    struct argument {
        using type =
            typename boost::mpl::at_c<boost::mpl::vector<As...>, I>::type;
    };

    static constexpr const unsigned int arity = sizeof...(As);
};

template<typename C>
struct callable_traits : public mem_fn_traits<decltype(&C::operator())>
{};

template<typename R, typename... Cs>
struct inline_visitor;

template<typename R, typename C, typename... Cs>
struct inline_visitor<R, C, Cs...> : public C, inline_visitor<R, Cs...> {
    using C::operator();
    using inline_visitor<R, Cs...>::operator();

    inline_visitor(C c, Cs... cs)
        : C(c), inline_visitor<R, Cs...>(cs...)
    {}
};

template<typename R, typename C>
struct inline_visitor<R, C> : public C, inline_visitor<R> {
    using C::operator();
    using inline_visitor<R>::operator();

    inline_visitor(C c) : C(c)
    {}
};

template<typename R>
struct inline_visitor<R> : public boost::static_visitor<R> {
    template<typename T>
    R operator()(T&&) const
    {
        throw std::runtime_error("Operation not implemented");
    }
};

struct reduce_op {
    template<typename T1, typename T2>
    struct apply {
        static_assert(std::is_same<T1, T2>::value,
                      "Cannot reduce not identical types");
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

struct extract_result_type_op {
    template<typename C>
    struct apply {
        using type = typename callable_traits<C>::result_type;
    };
};

template<typename S>
struct extract_result_type : boost::mpl::transform<
    S
  , extract_result_type_op
  >
{};

struct extract_argument_type_op {
    template<typename C>
    struct apply {
        using type = typename callable_traits<C>::template argument<0>::type;

        static_assert(callable_traits<C>::arity == 1, "Not a unary callable");
    };
};

template<typename S>
struct extract_argument_type : boost::mpl::transform<
    S
  , extract_argument_type_op
  >
{};

template<typename S, typename U = void>
struct has_unique_elements : public std::false_type
{};

template<typename S>
struct has_unique_elements<
    S
  , typename std::enable_if<
        boost::mpl::equal_to<
            boost::mpl::size<
                typename boost::mpl::unique<
                    S
                  , std::is_same<boost::mpl::_1, boost::mpl::_2>
                  >::type
              >
          , boost::mpl::size<S>
          >::value
      >::type
  > : public std::true_type
{};

template<typename... Cs>
auto make_inline_visitor(Cs&&... cs)
{
    using unique_arg_types = has_unique_elements<
        typename extract_argument_type<boost::mpl::vector<Cs...>>::type
      >;
    static_assert(unique_arg_types::value, "Argument types are not unique");

    using result_type = reduce<
        typename extract_result_type<boost::mpl::vector<Cs...>>::type
      >;
    return inline_visitor<typename result_type::type, Cs...>(std::forward<Cs>(cs)...);
}
} // detail

template<typename V, typename... Cs>
auto apply_inline_visitor(const V& v, Cs&&... cs)
{
    return boost::apply_visitor(
                detail::make_inline_visitor(std::forward<Cs>(cs)...), v);
}

using namespace std;
using namespace boost;

BOOST_AUTO_TEST_CASE(apply_inline_visitor_test)
{
    variant<int, string> v("test");
    BOOST_CHECK_EQUAL(
        apply_inline_visitor(v,
            [](int val) -> string { return lexical_cast<string>(val); },
            [](const string& val) -> string { return val; }
        ),
        "test"
    );
    v = 123;
    BOOST_CHECK_EQUAL(
        apply_inline_visitor(v,
            [](int val) -> string { return lexical_cast<string>(val); },
            [](const string& val) -> string { return val; }
        ),
        "123"
    );
    BOOST_REQUIRE_THROW(
        apply_inline_visitor(v,
            [](double val) -> string { return lexical_cast<string>(val); }
        ),
        runtime_error
    );
    BOOST_REQUIRE_THROW(apply_inline_visitor(v), runtime_error);
}
