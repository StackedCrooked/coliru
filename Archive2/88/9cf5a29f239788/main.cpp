#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <iostream>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

using namespace std;
using namespace boost;

namespace qi = spirit::qi;
namespace phx = phoenix;

template <typename Iterator, typename Action>
struct two_numbers : qi::grammar<Iterator, void (Action const&)>
{
    two_numbers() : two_numbers::base_type(start)
    {
        using namespace qi;
        start = int_ [ phx::bind(phx::cref(_r1), qi::_1) ] >> ' ' >> int_;
    }
    qi::rule<Iterator, void (Action const&)> start;
};

int main ()
{
    string input { "42 21" };
    auto first=std::begin (input), last=std::end(input);

    static const auto my_action = [] (auto&& p) {
        cout << "the meaning of life is " << p << "\n";
    };

    static const two_numbers <decltype(first), decltype (my_action)> p;

    if (qi::parse (first, last, p(phx::ref(my_action))))
        cout << "parse ok\n";
}
