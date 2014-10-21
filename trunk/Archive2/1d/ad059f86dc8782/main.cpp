#include <boost/preprocessor/seq/enum.hpp>
#include <boost/preprocessor/seq/transform.hpp>
#include <boost/preprocessor/variadic/to_seq.hpp>

#define ID_OP(_, func, elem) func(elem)
#define APPLY_TO_ALL(func, ...)               \
    BOOST_PP_SEQ_ENUM(                        \
	BOOST_PP_SEQ_TRANSFORM(                   \
		ID_OP, func,                          \
		BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__) \
	))

#define SomeTransformation(x) #x // stringize

APPLY_TO_ALL(SomeTransformation, 1, 2, 3)