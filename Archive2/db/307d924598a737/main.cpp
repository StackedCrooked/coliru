#include <iostream>
#include <string>
#include <vector>

#include <boost/assign/list_of.hpp>

struct test
{
    static std::vector<std::string> s_foo;
};

std::vector<std::string> test::s_foo = boost::assign::list_of("first_el")("second_el");

int main()
{
    for(size_t i = 0; i < test::s_foo.size(); ++i)
    {
        std::cout << test::s_foo[i] << " ";
    }
    return 0;
}
