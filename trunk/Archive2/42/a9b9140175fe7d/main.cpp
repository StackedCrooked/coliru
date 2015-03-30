#include <iostream>
#include <string>
#include <vector>

#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/phoenix/operator.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/repository/include/qi_seek.hpp>

namespace Format
{
    using namespace boost::spirit::qi;
    using namespace boost::spirit::repository::qi;

    using Value = boost::fusion::vector<int, int>;
    using Sequence = std::vector<Value>;

    template<class It>
    struct Grammar : grammar<It, Sequence(), blank_type>
    {
        Grammar() : Grammar::base_type(start)
        {
            start =
                '{' >> eol >> *("#" >> seek[eol] | pair >> eol) >> '}' >> eol
                ;

            pair =
                int_ >> ':' >> int_;
        }

        rule<It, Sequence(), blank_type> start;
        rule<It, Value(), blank_type> pair;
    };

    template<class It>
    bool Parse(It begin, It end, Sequence& ret)
    {
        static Grammar<It> grammar;
        return phrase_parse(begin, end, grammar, blank, ret);
    }
}

int main()
{
    char const input[] =
        R"({
#ignore
123:123
456:456
}
)";

    Format::Sequence seq;
    if (Format::Parse(std::begin(input), std::end(input), seq))
    {
        for (auto&& i : seq)
        {
            std::cout << i << "\n";
        }
    }
    else
        std::cout << "FAIL\n";
}