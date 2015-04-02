#include <boost/preprocessor/arithmetic/mul.hpp>
#include <boost/preprocessor/arithmetic/div.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/size.hpp>
#include <boost/preprocessor/variadic/to_tuple.hpp>
#include <boost/preprocessor/stringize.hpp>

#define DECLARE_ENUM(z, N, T) \
  BOOST_PP_TUPLE_ELEM(BOOST_PP_MUL(2, N), T) = N
#define DECLARE_NAME(z, N, T) \
  BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(BOOST_PP_MUL(2, N), T))
#define DECLARE_PATTERN(z, N, T) \
  BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(BOOST_PP_INC(BOOST_PP_MUL(2, N)), T))

#define DECLARE_VALUES_(T) \
  enum class IDs          { BOOST_PP_ENUM(BOOST_PP_DIV(BOOST_PP_TUPLE_SIZE(T), 2), DECLARE_ENUM   , T) }; \
  char const *names  [] = { BOOST_PP_ENUM(BOOST_PP_DIV(BOOST_PP_TUPLE_SIZE(T), 2), DECLARE_NAME   , T) }, \
             *pattern[] = { BOOST_PP_ENUM(BOOST_PP_DIV(BOOST_PP_TUPLE_SIZE(T), 2), DECLARE_PATTERN, T) };

#define DECLARE_VALUES(...) DECLARE_VALUES_(BOOST_PP_VARIADIC_TO_TUPLE(__VA_ARGS__))

DECLARE_VALUES(Peter  , 123,
               Karl   , 456,
               Volkard, Tuntenfriseurstammkunde)

#include <iostream>

int main()
{
    std::cout << (int)IDs::Peter << ' ' << (int)IDs::Karl << ' ' << (int)IDs::Volkard << '\n';
	for (auto c : names) std::cout << c << '\n';
	for (auto c : pattern) std::cout << c << '\n';
}
