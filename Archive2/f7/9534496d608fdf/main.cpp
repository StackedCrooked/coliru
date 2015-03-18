#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace qi = boost::spirit::qi;

namespace horus { namespace parsergenerator { namespace nmea {

    struct CardinalDirection {
        enum class Direction { EAST, NORTH, WEST, SOUTH };
    };

    struct PositionalDegreeImpl {
        PositionalDegreeImpl(CardinalDirection::Direction direction, double d)
         : _dir(direction), _degrees(d)
        {
        }

        double degrees() const { return _degrees; }

      private:
        CardinalDirection::Direction _dir;
        double _degrees;
    };

    template<typename Iterator, typename T = PositionalDegreeImpl>
    struct PositionalDegreeGrammar : qi::grammar<Iterator,T()>
    {
        PositionalDegreeGrammar() : PositionalDegreeGrammar::base_type(r)
        {
            r = (qi::double_ >> ',' >> type_)
                [
                    qi::_val = boost::phoenix::construct<T>(qi::_2,qi::_1)
                ];
        }
      private:
        struct Type_ : qi::symbols<char, CardinalDirection::Direction> {
            Type_() {
                this->add
                    ("E", CardinalDirection::Direction::EAST)
                    ("N",  CardinalDirection::Direction::NORTH)
                    ("W",  CardinalDirection::Direction::WEST)
                    ("S",  CardinalDirection::Direction::SOUTH);
            }
        } type_;

        qi::rule<Iterator,T()> r;
    };

} } }

int main() 
{
    using namespace horus::parsergenerator::nmea;
    typedef std::string::const_iterator It;

    PositionalDegreeImpl val(CardinalDirection::Direction::EAST, 1.0);

    PositionalDegreeGrammar<It> pos_deg_parser;

    std::string const str = "123.2,W";  
    It f = str.begin(), l = str.end();

    bool r = qi::parse(f, l, pos_deg_parser, val);

    if (r)
        std::cout << val.degrees() << ": " << std::boolalpha << (123.2==val.degrees()) << "\n";
    else
        std::cout << "parsing failed\n";
}
