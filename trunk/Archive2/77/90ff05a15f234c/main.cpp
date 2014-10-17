#include <iostream>
#include <boost/spirit/include/qi.hpp>
#include <boost/phoenix/bind.hpp>
#include <boost/phoenix/function.hpp>

using namespace std;
using namespace boost;

namespace qi = spirit::qi;
namespace phx = phoenix;

template <typename Iterator, typename Action>
struct two_numbers : qi::grammar<Iterator, void (Action)>
{
  two_numbers() : two_numbers::base_type(start)
  {
    using namespace qi;
    start %= int_ [ _r1 ] >> ' ' >> int_;
  }
  qi::rule<Iterator, void (Action)> start;
};

struct print_impl
{
    typedef void result_type;

    template <typename Arg>
    void operator()(Arg arg1) const
    {
        cout << "the meaning of life is " << arg1 << "\n";
    }
};

const phx::function<print_impl> print;

int main ()
{
  string input { "42 21" };
  auto first=std::begin (input), last=std::end(input);

  static const two_numbers <decltype(first), decltype (print)> p;

  if (qi::parse (first, last, p(phx::ref(print))))
  	cout << "parse ok\n";
}