#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(dummy_positive_test)
{
  BOOST_CHECK_EQUAL(0, 0);
}

BOOST_AUTO_TEST_CASE(dummy_negative_test)
{
  BOOST_CHECK_EQUAL(0, 1);
}
