#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/tti/has_type.hpp>
#include <type_traits>

#define BOOST_TTI_BOX_TYPE(U)           \
template<class T>                       \
struct box_type_ ## U                   \
{                                       \
        using type = typename T::U;     \
};

BOOST_TTI_HAS_TYPE(X)
BOOST_TTI_BOX_TYPE(X)
using default_X = int;

template<class T>
struct X_trait
:
        boost::mpl::eval_if<
                has_type_X<T>,
                box_type_X<T>,
                boost::mpl::identity<default_X>
        >
{};

template<class T>
using X_trait_t = typename X_trait<T>::type;

struct T1 { /* X defaults to int */ };
struct T2 { using X = char; };

int main()
{
    static_assert(std::is_same<X_trait_t<T1>, int >::value, "");
    static_assert(std::is_same<X_trait_t<T2>, char>::value, "");
}
