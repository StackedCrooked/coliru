#include <boost/algorithm/string.hpp>
#include <boost/preprocessor.hpp>
#include <iostream>
 
#define ELEMENT(n, product) \
    BOOST_PP_TUPLE_ELEM(BOOST_PP_SEQ_SIZE(product), n, BOOST_PP_SEQ_TO_TUPLE(product))
 
#define COMBINER(r, product) \
    ELEMENT(2, product) \
    ELEMENT(1, product) \
    ELEMENT(0, product);
 
#define TEST(args) \
    BOOST_PP_SEQ_FOR_EACH_PRODUCT(COMBINER, args)
 
#define TEST_STRING(args) \
    BOOST_PP_STRINGIZE(TEST(args))

#define EMPTY
 
int main()
{
    std::cout << "Types:" << std::endl;
    std::string s = TEST_STRING(
        ((her)(him)(nobody))
        ((marries)(divorces))
        ((he))
        );
    boost::replace_all(s, "; ", "\n");
    boost::replace_all(s, ";", "\n"); // last one has no space
    std::cout << s;
}