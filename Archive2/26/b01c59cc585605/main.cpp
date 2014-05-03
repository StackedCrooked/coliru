#include <boost/fusion/adapted/struct.hpp>
#include <boost/spirit/include/qi.hpp>

namespace qi = boost::spirit::qi;

struct FreqLevelPair
{
    float freq;
    float dbLevel;
};

BOOST_FUSION_ADAPT_STRUCT(
    FreqLevelPair,
    (float, freq)
    (float, dbLevel)
)

struct BroadbandCurve
{
    std::vector<FreqLevelPair> freqPairs;
    int numFreqPairs; //Ignored since we can just count the number of pairs outright...
    int curveNum; //ID number
};

BOOST_FUSION_ADAPT_STRUCT(
    BroadbandCurve,
    (std::vector<FreqLevelPair>, freqPairs)
    (int, numFreqPairs)
    (int, curveNum)
)

int main()
{
    typedef std::string::const_iterator Iterator;
    typedef qi::space_type Skipper;

    qi::real_parser<double, qi::strict_real_policies<double> > strict_real_;

    qi::rule<Iterator, BroadbandCurve(), Skipper> Cmd_BBNSET;
    Cmd_BBNSET = +(strict_real_ >> strict_real_) >> qi::int_ >> qi::int_ >> qi::lit("BBNSET");

    std::string const input("0.0 80.0 50.0 25.0 100.0 10.0 3 0 BBNSET");
    auto f(input.begin()), l(input.end());
    bool ok = qi::phrase_parse(f, l, Cmd_BBNSET, qi::space);

    if (ok)
    {
        std::cout << "Parse succeeded\n";
    } else
    {
        std::cout << "Parse failed\n";
    }

    if (f!=l)
        std::cout << "Remaining unparsed: '" << std::string(f,l) << "'\n";
}
