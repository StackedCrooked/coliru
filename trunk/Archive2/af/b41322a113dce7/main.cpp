#include <boost/fusion/adapted.hpp>
#include <boost/fusion/sequence/io/out.hpp>
#include <boost/fusion/sequence/intrinsic.hpp>
#include <boost/fusion/view.hpp>
#include <iostream>

namespace fuz = boost::fusion;

namespace demo
{
    using boost::fusion::operators::operator<<; // in order to write line 33
    struct employee
    {
        std::string name;
        int age;
    };
}

// demo::employee is now a Fusion sequence
BOOST_FUSION_ADAPT_STRUCT(
    demo::employee,
    (std::string, name)
    (int, age))

int main()
{
    demo::employee e;
    e.name = "bob";
    e.age = 42;

    std::cout << fuz::at_c<0>(e) << std::endl; 

    std::cout << e << std::endl;

    // fusion view
    std::cout << fuz::as_nview<0, 1>(e) << std::endl;
}
