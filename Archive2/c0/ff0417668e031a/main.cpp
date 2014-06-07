#include <boost/fusion/adapted/struct.hpp>
#include <boost/spirit/include/qi.hpp>

namespace qi = boost::spirit::qi;

struct record {
    std::string name;
    char x, y, cost;

    friend std::ostream& operator<<(std::ostream& os,const record& r) {
        return os << r.name << "\t" << int(r.x) << "\t" << int(r.y) << "\t" << int(r.cost);
    }
};

BOOST_FUSION_ADAPT_STRUCT(record, (std::string, name)(char, x)(char, y)(char, cost))

int main()
{
    std::istringstream iss(
            "1_3,1,3,0\n"
            "16_92,16,92,76\n"
            "8_31,8,31,13\n"
            "3_45,3,45,46\n"
            "12_67,12,67,66\n"
            "17_27,17,27,2\n"
            "7_72,7,72,74\n"
            "0_36,0,36,25\n"
            "18_30,18,30,50\n"
            "6_35,6,35,19\n"
            "16_5,16,5,50"
        );

    boost::spirit::istream_iterator f(iss >> std::noskipws), l;

    std::vector<record> data;
    bool ok = qi::phrase_parse(f, l,
        (qi::lexeme[+~qi::char_(',')]
         >> ',' >> qi::int_ >> ',' >> qi::int_ >> ',' >> qi::int_
        ) % qi::eol,
        qi::blank,
        data);

    if (ok)
    {
        std::cout << "Parsed success: " << data.size() << " records\n";
        for(auto& r : data)
            std::cout << r << "\n";
    } else
    {
        std::cout << "Parse failed\n";
    }

    if (f!=l)
    {
        std::cout << "Remaining unparsed input: '" << std::string(f,l) << "'\n";
    }
}
