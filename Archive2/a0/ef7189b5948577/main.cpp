#include <boost/fusion/adapted/struct.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/tuple/tuple_io.hpp>

namespace qi = boost::spirit::qi;

struct Staff
{
    std::string title;
    std::string firstName;
    std::string familyName;
    std::string position;
    std::string room;
    std::string email;
};

BOOST_FUSION_ADAPT_STRUCT(Staff, 
    (std::string, title)
    (std::string, firstName)
    (std::string, familyName)
    (std::string, position)
    (std::string, room)
    (std::string, email))

template <typename It, typename Skipper = qi::unused_type>
    struct grammar : qi::grammar<It, Staff(), Skipper>
{
    grammar() : grammar::base_type(start)
    {
        using namespace qi;
        column = lexeme [ *~char_("\t\r\n") ];
        start  = column >> '\t'  >> column >> '\t' >> column >> '\t' >> column >> '\t' >> column >> '\t' >> column;
    }
    private:
    qi::rule<It, std::string(), Skipper> column;
    qi::rule<It, Staff(), Skipper> start;
};

int main()
{
    std::cin.unsetf(std::ios::skipws);

    typedef boost::spirit::istream_iterator It;
    grammar<It> grammar;

    It f(std::cin), l;
    std::vector<Staff> staff_members;
    bool ok = qi::parse(f, l, grammar % qi::eol, staff_members);

    if (ok)
    {
        for(auto const& member : staff_members)
        {
            std::cout << boost::fusion::as_vector(member) << "\n";
        }
    } else
    {
        std::cout << "Parsing failed\n";
    }

    if (f != l)
        std::cout << "Remaining input '" << std::string(f, l) << "'\n";
}
