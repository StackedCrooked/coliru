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

static int relay_unit_test_main(std::vector<std::string> args);

int main()
{
    if (int const child_pid = fork())
    {
        int exit_code = relay_unit_test_main({"--run_test=suite1"});

        int child_exit_code;
        while (-1 == waitpid(child_pid, &child_exit_code, 0));
        if (!WIFEXITED(child_exit_code)) {
            std::cerr << "Child process (" << child_pid << ") failed" << std::endl;
            return 1;
        }

        return exit_code? exit_code : child_exit_code;
    } else
    {
        return relay_unit_test_main({"--run_test=suite2"});
    }
}

static bool init_function() { return true; }

static int relay_unit_test_main(std::vector<std::string> args)
{
    std::vector<char const*> c_args;
    c_args.push_back("fake_program_name");
    std::transform(args.begin(), args.end(), std::back_inserter(c_args), std::mem_fn(&std::string::data));
    c_args.push_back(nullptr);

    return unit_test_main( &init_function, c_args.size()-1, const_cast<char**>(c_args.data()) );
}

