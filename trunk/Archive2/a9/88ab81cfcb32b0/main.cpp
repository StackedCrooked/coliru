#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/variadic/to_seq.hpp>

    #define ID_OP(_, func, elem) func(elem)
    #define APPLY_TO_ALL(func, ...)                \
        BOOST_PP_SEQ_FOR_EACH(                     \
    		ID_OP, func,                           \
    		BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__)  \
    	)

#define SomeTransformation(x) #x // stringize

APPLY_TO_ALL(SomeTransformation, 1, 2, 3)