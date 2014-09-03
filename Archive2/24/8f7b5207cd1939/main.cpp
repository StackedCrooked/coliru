#include <string>
#include <boost/utility.hpp>

struct some_policy
{
    typedef boost::integral_constant<bool, false> condition;
};

struct other_policy
{
    typedef boost::integral_constant<bool, true> condition;
};


template <typename policy>
class test
{
   void do_something(typename boost::enable_if<typename policy::condition>::type* = 0) {}
};

int main()
{
    test<other_policy> p1;
    test<some_policy>  p2;
}
