#include <boost/assert.hpp>
#include <boost/variant.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/find_if.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/type_traits.hpp>

#include <type_traits>

#include <cstdlib>

template <typename ... Args>
struct is_constructible_pred
{
    template <typename T>
    struct apply
    {
        typedef std::is_constructible<T, Args...> type;
    };
};

template<class T, typename... Args>
decltype(void(T{std::declval<Args>()...}), std::true_type())
test(int);

template<class T, typename... Args>
std::false_type
test(...);

template<class T, typename... Args>
struct is_braces_constructible : decltype(test<T, Args...>(0))
{
};

template <typename ... Args>
struct is_braces_constructible_pred
{
    template <typename T>
    struct apply
    {
        typedef is_braces_constructible<T, Args...> type;
    };
};



struct A
{
    A() = default;
};

static_assert( std::is_constructible< A >::value,           " A()"        );
static_assert(!std::is_constructible< A, int >::value,      "!A(int)"     );
static_assert(!std::is_constructible< A, int, int >::value, "!A(int, int)");

struct B
{
    B(int) {}
};

static_assert(!std::is_constructible< B >::value,           "!B()"        );
static_assert( std::is_constructible< B, int >::value,      " B(int)"     );
static_assert(!std::is_constructible< B, int, int >::value, "!B(int, int)");

struct C
{
    int _1;
    int _2;
};

static_assert(!std::is_constructible< C, int, int>::value,      "!C(int, int)"     );
static_assert( is_braces_constructible< C, int, int >::value, " C{int, int}");

using V = boost::variant< A, B, C >;

template < typename V, typename Iter, typename ...O>
inline constexpr
V construct_impl(boost::mpl::true_, O &&... _o) //when there is a type that fulfills the predicate
{
    using deduced_type = typename boost::mpl::deref< Iter >::type;
    return deduced_type{std::forward< O >(_o)...};
}

template < typename V, typename Iter, typename ...O>
inline constexpr
V construct_impl(boost::mpl::false_, O &&... _o)//when there isn't any type that fulfills the predicate
{
    return V{};
}
template< typename V,
          typename ...O >
inline constexpr
V construct(O &&... _o)
{
    using types = typename V::types;
    using parens_pred = boost::mpl::apply1<is_constructible_pred< O... >,boost::mpl::_1>; 
    using braces_pred = boost::mpl::apply1<is_braces_constructible_pred< O...>,boost::mpl::_1>;
    using iter = typename boost::mpl::find_if< types, boost::mpl::or_<parens_pred,braces_pred> >::type;
    using type_found = typename boost::mpl::not_<typename boost::is_same<iter,typename boost::mpl::end<types>::type>::type>::type;
    static_assert(type_found::value,"There isn't any type in the variant that fulfills the predicate");
    return construct_impl<V,iter>(type_found(),std::forward<O>(_o)...);
}

struct type_printer:boost::static_visitor<>
{
    void operator()(A)const
    {
        std::cout << "A" << std::endl;
    }
    void operator()(B)const
    {
        std::cout << "B" << std::endl;
    }
    void operator()(C)const
    {
        std::cout << "C" << std::endl;
    }
};

int main()
{
    V a = construct< V >();
    boost::apply_visitor(type_printer(),a);
    BOOST_ASSERT(a.type() == typeid(A));
    V b = construct< V >(0);
    boost::apply_visitor(type_printer(),b);
    BOOST_ASSERT(b.type() == typeid(B));
    V c = construct< V >(0, 0);
    boost::apply_visitor(type_printer(),c);
    BOOST_ASSERT(c.type() == typeid(C));
    return EXIT_SUCCESS;
}