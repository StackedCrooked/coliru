#define BOOST_SPIRIT_DEBUG
#include <boost/spirit/include/qi.hpp>
#include <iostream>

namespace qi    = boost::spirit::qi;

struct data_t
{
    std::string label;
    enum Choice { left, right, up, down } choice;

    data_t(std::string label="default", Choice choice=left): label(std::move(label)), choice(choice) {}

    friend std::ostream& operator<<(std::ostream& os, Choice const& v) {
        switch(v) { 
            case left: return os << "left";
            case right:return os << "right";
            case up:   return os << "up";
            case down: return os << "down";
            default:   return os << "?";
        }
    }
    friend std::ostream& operator<<(std::ostream& os, data_t const& v) {
        return os << "{label:" << v.label << ";choice:" << v.choice << "}";
    }
};


template <typename It, typename Skipper = qi::space_type>
    struct parser : qi::grammar<It, data_t(), Skipper>
{
    parser() : parser::base_type(start)
    {
        using namespace qi;

        choice_.add
            ("left",  data_t::left)
            ("right", data_t::right)
            ("up",    data_t::up)
            ("down",  data_t::down);

        start %= as_string[ lexeme[+graph] ] >> lexeme [choice_];

        BOOST_SPIRIT_DEBUG_NODE(start);
    }

  private:
    qi::symbols<char, data_t::Choice> choice_;
    qi::rule<It, data_t(), Skipper> start;
};

bool doParse(const std::string& input)
{
    typedef std::string::const_iterator It;
    auto f(begin(input)), l(end(input));

    parser<It, qi::space_type> p;
    data_t data;

    try
    {
        bool ok = qi::phrase_parse(f,l,p,qi::space,data);
        if (ok)   
        {
            std::cout << "parse success\n";
            std::cout << "data: " << data << "\n";
        }
        else      std::cerr << "parse failed: '" << std::string(f,l) << "'\n";

        if (f!=l) std::cerr << "trailing unparsed: '" << std::string(f,l) << "'\n";
        return ok;
    } catch(const qi::expectation_failure<It>& e)
    {
        std::string frag(e.first, e.last);
        std::cerr << e.what() << "'" << frag << "'\n";
    }

    return false;
}

int main()
{
    bool ok = doParse("label1 up");
    return ok? 0 : 255;
}
