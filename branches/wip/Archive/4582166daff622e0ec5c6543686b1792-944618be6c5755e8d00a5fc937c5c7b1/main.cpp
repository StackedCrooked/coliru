#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/local.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <utility>
#include <string>
#include <map>

// MARKER

namespace FooConstants{
    const std::string foo0 = "foo0";
    const std::string foo1 = "foo1";
    const std::string foo2 = "foo2";
    const std::string foo3 = "fooN";
}

namespace metadata {

const std::map<int, std::string> constants = {

#define BOOST_PP_LOCAL_MACRO(n) \
   BOOST_PP_COMMA_IF(n) \
   std::make_pair(n, BOOST_PP_CAT(FooConstants::foo,n))

#define BOOST_PP_LOCAL_LIMITS (0, 3)

#include BOOST_PP_LOCAL_ITERATE()
 };
}

int main() {}
