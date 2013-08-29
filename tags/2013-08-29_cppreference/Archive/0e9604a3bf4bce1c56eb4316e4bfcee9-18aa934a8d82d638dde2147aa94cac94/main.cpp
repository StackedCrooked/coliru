#include <iostream>
#include <thread>
#include <algorithm>
#include <list>

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/seq/for_each.hpp>

#define SEQ (w)(x)(y)(z)

#define MACRO(r, data, elem) BOOST_PP_CAT(elem, data)

BOOST_PP_SEQ_FOR_EACH(MACRO, _, SEQ)

int main()
{

}