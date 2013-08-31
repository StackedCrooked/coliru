//#define BOOST_SPIRIT_DEBUG
#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/fusion/adapted.hpp>
#include <boost/variant.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/phoenix.hpp>
namespace qi    = boost::spirit::qi;
namespace karma = boost::spirit::karma;
namespace phx   = boost::phoenix;

struct regex
{
    std::string _pattern;
    explicit regex(std::string const& pattern) : _pattern(pattern) {}
};

typedef boost::variant<double, int, std::string, regex> value;

enum logicOp { logicOr, logicAnd, logicPositive };

struct condition
{
    bool          _negated;
    std::string   _propertyname;
    value         _operand;      // value or regex
};

struct filter
{
    logicOp   _op;
    condition _cond;
};

struct setcommand
{
    typedef std::list<std::pair<std::string, value> > pairs;
    pairs _propvals;
};

struct printcommand
{
    std::vector<std::string> _propnames;
};

typedef boost::variant<printcommand, setcommand> command;

struct statement
{
    std::vector<filter> _filters;
    command             _command;
};

BOOST_FUSION_ADAPT_STRUCT(regex, (std::string, _pattern));
BOOST_FUSION_ADAPT_STRUCT(printcommand, (std::vector<std::string>, _propnames));
BOOST_FUSION_ADAPT_STRUCT(setcommand, (setcommand::pairs, _propvals));
BOOST_FUSION_ADAPT_STRUCT(condition, (bool, _negated)(std::string, _propertyname)(value, _operand));
BOOST_FUSION_ADAPT_STRUCT(filter, (logicOp, _op)(condition, _cond));
BOOST_FUSION_ADAPT_STRUCT(statement, (std::vector<filter>, _filters)(command, _command));

// see http://stackoverflow.com/a/14206443/85371
namespace boost { namespace phoenix { namespace stl {
    template <typename This, typename Key, typename Value, typename Compare, typename Allocator, typename Index>
        struct at_impl::result<This(std::map<Key,Value,Compare,Allocator>&, Index)>
        { typedef Value & type; };
    template <typename This, typename Key, typename Value, typename Compare, typename Allocator, typename Index>
        struct at_impl::result<This(std::map<Key,Value,Compare,Allocator> const&, Index)>
        { typedef Value const& type; };
}}}

template <typename It, typename Delim>
    struct generator : karma::grammar<It, statement(), Delim>
{
    generator() : generator::base_type(start)
    {
        using namespace karma;

        property_  = karma::string;
        strlit_    = '"'  << karma::string << '"';
        regex_     = "m/" << karma::string << "/";

        value_     = (double_ | int_ | strlit_ | regex_);
        negate_    = eps [ _pass = !_val ] | lit("NOT");

        condition_ = negate_  << property_  << '=' << value_;
        print_     = "PRINT " << property_ % ", ";
        set_       = "SET "   << (property_ << '=' << value_) % ", ";
        command_   = print_ | set_;

        static const auto logicOpNames = std::map<logicOp, std::string> { 
            { logicPositive, "WHERE" },
            { logicAnd, "AND" },
            { logicOr, "OR" } };

        logic_ = string [ _1 = phx::at(phx::cref(logicOpNames), _val) ];

        filters_ = +(logic_ << condition_);

        statement_ = filters_ << command_;

        start = statement_;
    }

  private:
    karma::rule<It, logicOp()            , Delim> logic_;
    karma::rule<It, statement()          , Delim> statement_;
    karma::rule<It, std::vector<filter>(), Delim> filters_;
    karma::rule<It, command()            , Delim> command_;
    karma::rule<It, condition()          , Delim> condition_;
    karma::rule<It, statement()          , Delim> start;
    karma::rule<It, bool()        > negate_;
    karma::rule<It, printcommand()> print_;
    karma::rule<It, setcommand()  > set_;
    karma::rule<It, std::string() > strlit_, property_;
    karma::rule<It, value()       > value_;
    karma::rule<It, regex()       > regex_;
};

template <typename It, typename Skipper = qi::space_type>
    struct parser : qi::grammar<It, statement(), Skipper>
{
    parser() : parser::base_type(start)
    {
        using namespace qi;

        // no-skipper rules
        property_  = alpha >> *alnum;
        strlit_    = '"' >> *(  (lit('\\') >> char_) | ~char_('"') ) > '"';

        // with-skipper rules
        regex_     = strlit_ [ _val = phx::construct<regex>(_1) ];
        value_     = double_ | int_ | strlit_;
        condition_ = (no_case["NOT"] >> attr(true) | attr(false)) 
            >> property_ 
            >> (
                    no_case["LIKE"] >> regex_ | '=' >> value_
               );

        print_   = no_case["PRINT"] >> property_ % ',';
        set_     = no_case["SET"] >> (property_ >> '=' >> value_) % ',';
        command_ = print_ | set_;

        filters_ %= +(
                (
                   no_case["WHERE"] [ _pass = (phx::size(_val) == 0) ] >> attr(logicPositive)
                 | no_case["AND"]   [ _pass = (phx::size(_val) >  0) ] >> attr(logicAnd)
                 | no_case["OR"]    [ _pass = (phx::size(_val) >  0) ] >> attr(logicOr)
                ) 
                >> condition_);

        statement_ = filters_ >> command_;

        start = statement_;
        BOOST_SPIRIT_DEBUG_NODES((start)(condition_)(value_)(strlit_)(regex_)(property_)(statement_)(filters_)(print_)(set_)(command_));
    }

  private:
    qi::rule<It, statement()          , Skipper> statement_;
    qi::rule<It, std::vector<filter>(), Skipper> filters_;
    qi::rule<It, printcommand()       , Skipper> print_;
    qi::rule<It, setcommand()         , Skipper> set_;
    qi::rule<It, command()            , Skipper> command_;
    qi::rule<It, std::string()                 > strlit_, property_; // no skipper
    qi::rule<It, value()              , Skipper> value_, regex_;
    qi::rule<It, condition()          , Skipper> condition_;
    qi::rule<It, statement()          , Skipper> start;
};

bool doParse(std::string const& input)
{
    auto f(begin(input)), l(end(input));

    parser<decltype(f), qi::space_type> p;
    statement parsed;

    bool ok = qi::phrase_parse(f,l,p,qi::space,parsed);
    if (ok)   
    {
        std::cout << "parse success: '" << input << "'\n";
        generator<boost::spirit::ostream_iterator, karma::space_type> gen;
        std::cout << "parsed: " << karma::format_delimited(gen, karma::space, parsed) << "\n";
    }
    else      
        std::cerr << "parse failed: '" << std::string(f,l) << "'\n";

    if (f!=l) 
        std::cerr << "trailing unparsed: '" << std::string(f,l) << "'\n";

    return ok;
}

int main()
{
    doParse("where currency like \"GBP|USD\" set logging = 1, logfile = \"myfile\"");
    doParse("where not status = \"ok\" print ident, errorMessage");
    doParse("where status = \"ok\" or not currency like \"GBP|USD\" print ident, errorMessage");
    // All the extra levels of escaping get a bit ugly here. Of course, you'd be reading from a file/database/etc...
    doParse("where status = \"\\\"special\\\"\" set logfile = \"C:\\\\path\\\\to\\\\logfile.txt\"");
}