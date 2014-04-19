#define BOOST_TEST_MAIN
#ifndef BOOST_TEST_DYN_LINK
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/bind.hpp>
using namespace boost::unit_test;

//____________________________________________________________________________//

BOOST_AUTO_TEST_SUITE(suite1)
    BOOST_AUTO_TEST_CASE(case1)
    {
        //my test code here
    }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(suite2)
    BOOST_AUTO_TEST_CASE(case1)
    {
        //my test code here
    }

    BOOST_AUTO_TEST_CASE(case2)
    {
        //my test code here
    }
BOOST_AUTO_TEST_SUITE_END()
