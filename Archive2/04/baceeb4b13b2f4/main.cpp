#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/phoenix.hpp>
#include <boost/spirit/include/qi.hpp>

namespace qi = boost::spirit::qi;

struct FreqLevelPair {
    float freq;
    float dbLevel;
};

struct BroadbandCurve {
    std::vector<FreqLevelPair> freqPairs;
    int curveNum;
};

struct MakeBroadbandCurve {
    template <typename V, typename Curve> struct result { typedef bool type; };
    template <typename V, typename Curve>
        bool operator()(V const& val, Curve& attr) const
        {
            if (val.size() % 2)
                return false;

            auto last = val.rbegin();
            attr.curveNum = static_cast<int>(*last++);
            auto numFreqPairs = static_cast<size_t>(*last++);

            for(auto it = val.begin(); it != last.base();)
            {
                auto a = static_cast<float>(*it++), 
                     b = static_cast<float>(*it++);
                attr.freqPairs.push_back({a, b});
            }

            return (numFreqPairs == attr.freqPairs.size());
        }
};

static const boost::phoenix::function<MakeBroadbandCurve> make_curve;

int main()
{
    typedef std::string::const_iterator Iterator;
    typedef qi::space_type Skipper;

    qi::rule<Iterator, BroadbandCurve(), Skipper> Cmd_BBNSET;
    Cmd_BBNSET = (+qi::double_ >> "BBNSET") [ qi::_pass = make_curve(qi::_1, qi::_val) ];

    //std::string const input("0.0 80.0 50.0 25.0 100.0 10.0 3 0 BBNSET");
    std::string const input("0 50 200 100 2 0 BBNSET");

    BroadbandCurve curve;

    auto f(input.begin()), l(input.end());
    bool ok = qi::phrase_parse(f, l, Cmd_BBNSET, qi::space, curve);

    if (ok)
    {
        std::cout << "Parse succeeded\n";
        std::cout << "curveNum: " << curve.curveNum << "\n";
        for(auto& p : curve.freqPairs)
            std::cout << "{ " << p.freq << ", " << p.dbLevel << " }\n";
    } else
    {
        std::cout << "Parse failed\n";
    }

    if (f!=l)
        std::cout << "Remaining unparsed: '" << std::string(f,l) << "'\n";
}
