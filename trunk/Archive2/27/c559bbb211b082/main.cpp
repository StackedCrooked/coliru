#include <boost/preprocessor/iteration/local.hpp>
#include <boost/preprocessor/cat.hpp>

#include <iostream>

#define BOOST_PP_LOCAL_MACRO(VAL) \
      int BOOST_PP_CAT(test_, VAL);

#define BOOST_PP_LOCAL_LIMITS (1, 10)


int main
{
    std::cout << test_2;
}
    