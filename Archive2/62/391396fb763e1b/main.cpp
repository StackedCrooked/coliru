#include <iostream>
#include <boost/fusion/adapted/boost_tuple.hpp>
#include <boost/spirit/include/karma.hpp>

int main()
{
    using Ring = std::vector<boost::tuple<double,double>>;

    std::vector<Ring> rings = {
        {   {   2, 1.3 }, { 2.4, 1.7 }, { 2.8, 1.8 }, { 3.4, 1.2 },
            { 3.7, 1.6 }, { 3.4,   2 }, { 4.1,   3 }, { 5.3, 2.6 },
            { 5.4, 1.2 }, { 4.9, 0.8 }, { 2.9, 0.7 }, {   2, 1.3 },
        },
        {   { 4.0, 2.0 }, { 4.2, 1.4 }, { 4.8, 1.9 }, { 4.4, 2.2 }, { 4.0, 2.0   },
        }
    };

    using namespace boost::spirit::karma;
    std::cout << format_delimited("POLYGON(" << *('(' << auto_%',' << ')') << ")\n", ' ', rings);
}
