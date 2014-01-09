#include <boost/spirit/include/qi.hpp>

namespace qi = boost::spirit::qi;

int main()
{
    std::string const example = "<member names=\"John:Frank\" family=\"Smith:Wesson\"/>";

    auto f = begin(example), l = end(example);
    std::vector<std::string> data;

    if (qi::parse(f, l,
             *(
                 qi::omit [ *~qi::char_('"') ] >> '"' >> qi::as_string [ *~qi::char_("\":") ] % ':' >> '"'
              ),
             data))
    {
        for (auto const& item : data)
            std::cout << item << "\n";
    }
}
