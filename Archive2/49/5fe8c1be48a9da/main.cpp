#include <boost/preprocessor/tuple/rem.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/for_each_product.hpp>

#define REF  (&&)(&)()
#define CV   (const volatile)(const)(volatile)()
#define VAR  (())((,...)) // Had to add a comma here and use rem_ctor below,
                          // otherwise Clang complains about ambiguous ellipses

#define SPEC(r, product) \
template <typename R, typename... Args> \
struct strip_function_qualifiers<R(Args... BOOST_PP_TUPLE_REM_CTOR( \
    BOOST_PP_SEQ_ELEM(0, product))) \
	BOOST_PP_SEQ_ELEM(1, product)   \
	BOOST_PP_SEQ_ELEM(2, product)>  \
{using type = R(Args... BOOST_PP_TUPLE_REM_CTOR( \
                        BOOST_PP_SEQ_ELEM(0, product)));};

template <typename> struct strip_function_qualifiers;

BOOST_PP_SEQ_FOR_EACH_PRODUCT(SPEC, (VAR)(CV)(REF))

template <typename T>
using strip_t = typename strip_function_qualifiers<T>::type;

#include <type_traits>
int main()
{
	static_assert( std::is_same<void()   , strip_t<void() const>>{}, "" );
	static_assert( std::is_same<void()   , strip_t<void() const&&>>{}, "" );
	static_assert( std::is_same<void(...), strip_t<void(...) const volatile&&>>{}, "" );
}
