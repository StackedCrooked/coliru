#include <boost/spirit/include/qi.hpp>

namespace qi = boost::spirit::qi;
namespace asc= boost::spirit::ascii;

int main()
{
    typedef std::string::const_iterator It;

    std::string const input("GOOSE BAY  LATITUDE   53.27    LONGITUDE   299.60    ALTITUDE    46 M");

    std::string name;
    double lat, lon, alt;

    It first(input.begin()), last(input.end());

    bool r = qi::phrase_parse(first, last,
            (qi::raw [ +(qi::char_ - "LATITUDE") ] >> "LATITUDE" >>
             qi::double_ >> "LONGITUDE" >> 
             qi::double_ >> "ALTITUDE" >> 
             qi::double_ >> "M"), 
            asc::space,
            name, lat, lon, alt);

    if (r)
        std::cout << "Parsed: '" << name << "' lat:" << lat << " lon:" << lon << " alt:" << alt << "\n";
    else
        std::cout << "Failed\n";

    if (first != last)
        std::cout << "Remaining input: '" << std::string(first, last) << "'\n";
}
