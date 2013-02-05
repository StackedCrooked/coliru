#include <boost/phoenix/core.hpp>
#include <boost/phoenix/operator.hpp>
#include <boost/phoenix/function.hpp>
#include <algorithm>
#include <iostream>
#include <string>


boost::phoenix::expression::argument<1>::type arg1;
struct flip_impl
{
    typedef std::string result_type;
    
    std::string operator()(std::string arg) const
    {
        using std::begin;
        using std::end;
        std::reverse(begin(arg), end(arg));
        return arg;
    }
};


boost::phoenix::function<flip_impl> flip;
auto flip2 = flip(flip(arg1));


int main()
{
    std::string abc = "abc";
    std::cout << flip(abc)() << std::endl;
    std::cout << flip2(abc)() << std::endl;
}
