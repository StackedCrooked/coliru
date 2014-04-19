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
        BOOST_CHECK(1==2); // THIS SHOULD FAIL :)
    }
BOOST_AUTO_TEST_SUITE_END()

#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>

static bool init_function() { return true; }

int main(int argc, char** argv)
{
    return unit_test_main(&init_function, argc, argv);
}
