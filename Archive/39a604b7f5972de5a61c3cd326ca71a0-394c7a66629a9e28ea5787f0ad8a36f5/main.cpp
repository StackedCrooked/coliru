#include <boost/fusion/adapted/struct.hpp>
#include <boost/fusion/include/for_each.hpp>
#include <boost/phoenix/phoenix.hpp>
using boost::phoenix::arg_names::arg1;

#include <string>
#include <iostream>

struct A
{
    int a;
    int b;
    std::string c;
};

BOOST_FUSION_ADAPT_STRUCT(A, (int,a)(int,b)(std::string,c))

int main()
{
    const A obj = { 1, 42, "The Answer To LtUaE" };

    boost::fusion::for_each(obj, std::cout << arg1 << "\n");
}
