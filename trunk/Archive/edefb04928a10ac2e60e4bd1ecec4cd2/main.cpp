#include <boost/phoenix/core.hpp>
#include <boost/phoenix/operator.hpp>
#include <boost/phoenix/function.hpp>
#include <iostream>


struct increment_impl
{
    template<typename Arg>
    struct result { typedef double type; };

    template<typename Arg>
    typename result<Arg>::type operator()(Arg n)
    {
        return static_cast<typename result<Arg>::type>(n) + 1;
    }
};


boost::phoenix::function<increment_impl> inc;


int main()
{
    std::cout << "Begin" << std::endl;
    std::cout << inc(1)() << std::endl;
    std::cout << "End" << std::endl;
}