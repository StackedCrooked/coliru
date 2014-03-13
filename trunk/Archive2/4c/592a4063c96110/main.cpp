#include <boost/range/algorithm.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/phoenix/phoenix.hpp>
#include <boost/phoenix/function/function.hpp>
#include <boost/typeof/typeof.hpp>

namespace phx = boost::phoenix;
using namespace phx::arg_names;

#include <iostream>
#include <vector>
#include <list>

class Foo
{
    int _i;
  public:
    Foo() : _i(rand() % 100) {};
    std::string Value() const { return boost::lexical_cast<std::string>(_i); }
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
    BOOST_AUTO(value_of, phx::lambda[ phx::bind(&Foo::Value, arg1) ]);

    FooList foos;
    for (int i = 0; i<10; ++i)
        foos.insert(foos.end(), Foo());

    std::vector<int> ints;
    boost::transform(
            foos, // generates 10 random element values
            back_inserter(ints), 
            lexical_casts::to_int(value_of(arg1)));

    for (FooList::const_iterator it = foos.begin(); it != foos.end(); ++it) 
        std::cout << it->Value() << " ";
    std::cout << "\n";

    for (size_t i = 0; i < ints.size(); ++i) 
        std::cout << ints[i] << " ";
    std::cout << "\n";
}

