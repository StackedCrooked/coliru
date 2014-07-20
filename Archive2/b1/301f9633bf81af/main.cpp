#include <boost/preprocessor.hpp>

// This works on both compilers, expands to ( a ) as expected
#define PARENS_AND_SUCH1(FLAG) BOOST_PP_IF(FLAG, BOOST_PP_LPAREN() a BOOST_PP_RPAREN(), b)

// MSVC: syntax error/unexpected end of file in macro expansion 
// NDK: unterminated argument list
#define PARENS_AND_SUCH2(FLAG) BOOST_PP_IF(FLAG, BOOST_PP_LPAREN() a, b)

// Desired expansion: ( a
// MSVC expansion: ( a, b )
// NDK: error: macro "BOOST_PP_IIF" requires 3 arguments, but only 2 given
#define PARENS_AND_SUCH3(FLAG) BOOST_PP_IF(FLAG,BOOST_PP_LPAREN() a, b BOOST_PP_RPAREN())

#define PARENS_AND_SUCH4(FLAG) BOOST_PP_LPAREN_IF(FLAG) BOOST_PP_IF(FLAG, a, b) BOOST_PP_RPAREN_IF(BOOST_PP_NOT(FLAG))


#define TRUE_HELPER() BOOST_PP_LPAREN() a
#define FALSE_HELPER() b BOOST_PP_RPAREN()
#define PARENS_AND_SUCH5(FLAG) BOOST_PP_IF(FLAG, TRUE_HELPER, FALSE_HELPER)()


PARENS_AND_SUCH4(0)
PARENS_AND_SUCH4(1)
PARENS_AND_SUCH5(0)
PARENS_AND_SUCH5(1)

