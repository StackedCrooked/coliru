#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE thread_test_module
#include <boost/test/unit_test.hpp>
#include <thread>

void do_nothing() {}

BOOST_AUTO_TEST_CASE ( boost_thread_test )
{
    std::thread t(do_nothing);
    t.join();
}