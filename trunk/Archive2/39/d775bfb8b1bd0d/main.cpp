#include <vector>
#include <map>
#include <cmath>

struct LRopeData {
    int X;
    int Y1;
    int Y2;

    double distanceToPoint(double px, double py) const
    {
        int y1(Y1), y2(Y2);
        // normalize segment endpoints (y1, y2)
        if (y1>y2) std::swap(y1, y2);

        double dx = (px - X);
        double dy = 0;

        if (py<y1)   dy = (py - y1);
        if (py > y2) dy = (py - y2);

        return sqrt(dx * dx + dy * dy);
    }
};

typedef int                    LRID;
typedef std::vector<LRopeData> LRData;
typedef std::map<LRID, LRData> LRMap;
typedef std::pair<LRID, LRData> LRPair;

LRMap CreateRopeStructure();

#include <algorithm>
#include <iostream>
#include <tr1/functional> // bind (for c++03)

int main()
{
    LRMap data = CreateRopeStructure();

    // ex. from OP
    int const ID = 10000;
    int const  X =  -500;
    int const  Y =   400;

    // select rope data by ID:
    LRData const& ropes = data[ID];

    if (ropes.empty())
    {
        std::cout << "infinite" << std::endl;
    } else
    {
        // get the distance to each rope
        std::vector<double> distances(ropes.size());
        std::transform(
                ropes.begin(), ropes.end(), 
                distances.begin(),
                std::tr1::bind(&LRopeData::distanceToPoint, std::tr1::placeholders::_1, X, Y));

        // print the shortest distance
        std::cout << *std::min_element(distances.begin(), distances.end()) << std::endl;
    }
}

#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/fusion/adapted.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <fstream>
#include <cassert>

BOOST_FUSION_ADAPT_STRUCT(LRopeData, (int,X)(int,Y1)(int,Y2))

LRMap CreateRopeStructure()
{
    // input
    std::ifstream ifs("input.txt");
    ifs >> std::noskipws;
    typedef boost::spirit::istream_iterator It;
    It f(ifs), l;

    // grammar
    using namespace boost::spirit::qi;
    rule<It, LRPair(), blank_type, locals<int> > lrmap;

    lrmap %= '[' >> int_ >> ']' >> +eol
          >> "total" >> '=' >> omit [ int_ [ _a = _1 ] ] >> +eol
          >> repeat(_a) [ int_ >> int_ >> int_ >> +eol ]
          ;

    // parse
    LRMap data;
    assert(phrase_parse(f, l, +lrmap, blank, data));

    if (f!=l)
        std::cout << "Remaining unparsed: '" << std::string(f,l) << "'\n";

    // done
    return data;
}

