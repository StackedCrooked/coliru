//#define BOOST_SPIRIT_DEBUG
#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/fusion/adapted/struct.hpp>
#include <boost/spirit/include/qi.hpp> 
#include <boost/spirit/include/qi_symbols.hpp>

static const char* YesNo(bool b) { return b?"Yes":"No"; }

struct Dog {
    std::string Name;
    bool        Barks;
    bool        HasATail;
    std::string Address;

    friend std::ostream& operator <<(std::ostream& os, Dog const& o) {
        return os << "[DOG|Name=" << o.Name << "|Barks=" << YesNo(o.Barks) << "|Has a Tail=" << YesNo(o.HasATail) << "|Address=" << o.Address << "]";
    }
}; 

struct Bird {
    std::string Name;
    bool        Tweets;
    std::string Address;

    friend std::ostream& operator <<(std::ostream& os, Bird const& o) {
        return os << "[BIRD|Name=" << o.Name << "|Tweets=" << YesNo(o.Tweets) << "|Address=" << o.Address << "]";
    }
};

typedef boost::variant<Dog, Bird> ZooAnimal;

BOOST_FUSION_ADAPT_STRUCT(Dog, (std::string, Name)(bool, Barks)(bool, HasATail)(std::string, Address))
BOOST_FUSION_ADAPT_STRUCT(Bird, (std::string, Name)(bool, Tweets)(std::string, Address))

namespace qi    = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

template <typename Iterator>
struct ZooGrammar : public qi::grammar<Iterator, ZooAnimal(), ascii::space_type>
{
    ZooGrammar() : ZooGrammar::base_type(start_)
    {
        using qi::_1;

        yesno_.add("Yes", true)("Y", true)("No", false)("N", false); 

        dog_ = qi::lit("DOG") >> '|' >> "Name=" >> lit_   >> '|'
                              >> "Barks="       >> yesno_ >> '|'
                              >> "Has a Tail="  >> yesno_ >> '|'
                              >> "Address="     >> lit_
             ;

        bird_ = qi::lit("BIRD") >> '|' >> "Name=" >> lit_   >> '|'
                                >> "Tweets="      >> yesno_ >> '|'
                                >> "Address="     >> lit_
              ;

        start_ = dog_ | bird_;

        lit_   = qi::lexeme [ *~qi::char_('|') ];

        BOOST_SPIRIT_DEBUG_NODES((dog_)(bird_)(start_)(lit_))
    } 

  private:
    qi::rule<Iterator, ZooAnimal(),   ascii::space_type> start_;
    qi::rule<Iterator, std::string(), ascii::space_type> lit_;
    qi::rule<Iterator, Dog(),         ascii::space_type> dog_;
    qi::rule<Iterator, Bird(),        ascii::space_type> bird_;
    qi::symbols<char, bool> yesno_; 
}; 

int main()
{
    typedef std::string::const_iterator iterator_type;
    typedef ZooGrammar<iterator_type> grammar;

    for (std::string const input : { 
            "DOG | Name=tim | Barks=Yes | Has a Tail=N | Address=3 infinite loop",
            "BIRD| Name=poc | Tweets=Yes| Address=10 stack overflow street"
            })
    {
        iterator_type start = input.begin(); 
        iterator_type end   = input.end();
        grammar g; 

        ZooAnimal animal;
        if(qi::phrase_parse(start, end, g, ascii::space, animal))
            std::cout << "Matched: " << animal << "\n";
        else
            std::cout << "Parse failed\n";

        if (start != end)
            std::cout << "Remaining input: '" << std::string(start, end) << "'\n";
    }
}
