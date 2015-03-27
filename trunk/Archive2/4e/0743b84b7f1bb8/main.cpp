#include <boost/spirit/home/qi.hpp>
namespace qi    = boost::spirit::qi;
namespace ascii = boost::spirit::qi::ascii;

template <typename Iterator>
struct Event_Bool_No_Param : qi::grammar<Iterator>
{
    Event_Bool_No_Param () 
        : Event_Bool_No_Param::base_type(start)
    {
        using qi::lit;

        start =
            lit("STATE_TIMEOUT") | lit("RAMPING_COMPLETED") | lit("PASSIVE_MEAS_COMPLETED")
            ;
    }
    qi::rule<Iterator> start;
};


template <typename Iterator, typename Skipper>
struct Event_Grammar : boost::spirit::qi::grammar<Iterator, Skipper>
{
    Event_Grammar() : Event_Grammar::base_type(start)
    {
        using boost::spirit::ascii::char_;

        start = 
            char_('@') >> char_('(') >> event_no_param >> char_(')')
            ;

    }
    qi::rule<Iterator, Skipper> start;
    Event_Bool_No_Param<Iterator> event_no_param;
};

int main()
{
    using iterator_t = std::string::const_iterator;
    std::string input = "@ ( STATE_TIMEOUT )";
    iterator_t iter = input.begin();
    iterator_t end = input.end();

    Event_Grammar<iterator_t,ascii::space_type> grammar;   

    bool ok = qi::phrase_parse( iter, end
            , grammar
            , ascii::space
            );

    return ok? 0 : 255;
}
