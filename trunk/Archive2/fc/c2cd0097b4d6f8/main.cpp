#include <boost/range/algorithm.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/phoenix/phoenix.hpp>
#include <boost/phoenix/function/function.hpp>
namespace phx = boost::phoenix;
using namespace phx::arg_names;

#include <iostream>
#include <vector>
#include <list>

class Foo
{
    int _i { rand() % 100 };
  public:
    std::string Value() const { return std::to_string(_i); }
};

namespace lexical_casts
{
    template <typename T> struct to_
    {
        template <typename> struct result { typedef T type; };
        template <typename V>
        T operator()(V const& v) const { return boost::lexical_cast<T>(v); }
    };

    boost::phoenix::function<to_<int> > to_int;
}

int main()
{
    srand(42);
    typedef std::list<Foo> FooList;
    auto value_of = phx::lambda[ phx::bind(&Foo::Value, arg1) ];

    std::vector<int> ints;
    boost::transform(
            FooList(10), // generates 10 random element values
            back_inserter(ints), 
            lexical_casts::to_int(value_of(arg1)));

    for (int i : ints) std::cout << i << " ";
}
