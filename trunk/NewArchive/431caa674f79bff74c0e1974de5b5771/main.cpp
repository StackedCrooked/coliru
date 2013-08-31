#include <boost/phoenix/core.hpp>
#include <boost/phoenix/operator.hpp>
#include <boost/phoenix/function.hpp>
#include <algorithm>
#include <iostream>
#include <string>


boost::phoenix::expression::argument<1>::type arg1;
struct flip_impl
{
    template<typename Arg>
    struct result
    {
        typedef Arg type;
    };
    
    template<typename Arg>
    auto operator()(Arg arg) const -> decltype(arg)
    {
        using std::begin;
        using std::end;
        std::reversea(begin(arg), end(arg));
        return arg;
    }
};


boost::phoenix::function<flip_impl> flip;


int main()
{
    std::string abc = "abc";
    std::cout << flip(abc) << std::endl;
}