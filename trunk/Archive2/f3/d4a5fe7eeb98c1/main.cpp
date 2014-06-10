//#define BOOST_SPIRIT_DEBUG
#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/fusion/adapted/struct.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/utility/string_ref.hpp>
#include <functional>
#include <map>

namespace mustache {

    // any atom refers directly to source iterators for efficiency
    using boost::string_ref;
    template <typename Kind> struct atom {
        string_ref value;

        atom() { }
        atom(string_ref const& value) : value(value) { }

        friend std::ostream& operator<<(std::ostream& os, atom const& v) { return os << typeid(v).name() << "[" << v.value << "]"; }
    };

    // the atoms
    using verbatim = atom<struct verbatim_tag>;
    using variable = atom<struct variable_tag>;
    using partial  = atom<struct partial_tag>;

    // the template elements (any atom or a section)
    struct section;

    using melement = boost::variant<
            verbatim,
            variable,
            partial, // TODO comments and set-separators
            boost::recursive_wrapper<section>
        >;

    // the template: sequences of elements
    using sequence = std::vector<melement>;

    // section: recursively define to contain a template sequence
    struct section {
        bool       sense; // positive or negative
        string_ref control;
        sequence   content;
    };
}

BOOST_FUSION_ADAPT_STRUCT(mustache::section, (bool, sense)(boost::string_ref, control)(mustache::sequence, content))

namespace qi = boost::spirit::qi;
namespace phx= boost::phoenix;

template <typename Iterator>
    struct mustache_grammar : qi::grammar<Iterator, mustache::sequence()>
{
    mustache_grammar() : mustache_grammar::base_type(sequence)
    {
        using namespace qi;
        static const _a_type section_id = {}; // local
        using boost::phoenix::construct;
        using boost::phoenix::begin;
        using boost::phoenix::size;
        
        sequence     = *element;
        element      = 
                    !(lit("{{") >> '/') >> // section-end ends the current sequence
                    (partial | section | variable | verbatim);

        reference    = raw [ lexeme [ +(graph - "}}") ] ]
                        [ _val = construct<boost::string_ref>(&*begin(_1), size(_1)) ];

        partial      = qi::lit("{{") >> "> " >> reference >> "}}";

        sense        = ('#' > attr(true))
                     | ('^' > attr(false));

        section     %= "{{" >> sense >> reference [ section_id = phx::bind(&boost::string_ref::to_string, _1) ] >> "}}"
                    >> sequence // contents
                    > ("{{" >> ('/' >> lexeme [ lit(section_id) ]) >> "}}");

        variable     = "{{" >> reference >> "}}";

        verbatim     = raw [ lexeme [ +(char_ - "{{") ] ]
                        [ _val = construct<boost::string_ref>(&*begin(_1), size(_1)) ];

        BOOST_SPIRIT_DEBUG_NODES(
                (sequence)(element)(partial)(variable)(section)(verbatim)
                (reference)(sense)
            )
    }
  private:
    qi::rule<Iterator, mustache::sequence()> sequence;
    qi::rule<Iterator, mustache::melement()> element;
    qi::rule<Iterator, mustache::partial()>  partial;
    qi::rule<Iterator, mustache::section(), qi::locals<std::string> >  section;
    qi::rule<Iterator, bool()>                sense;                  // postive  or negative
    qi::rule<Iterator, mustache::variable()> variable;
    qi::rule<Iterator, mustache::verbatim()> verbatim;
    qi::rule<Iterator, boost::string_ref()>   reference;
};

namespace Dumping {
    struct dumper : boost::static_visitor<std::ostream&>
    {
        std::ostream& operator()(std::ostream& os, mustache::sequence const& v) const {
            for(auto& element : v)
                boost::apply_visitor(std::bind(dumper(), std::ref(os), std::placeholders::_1), element);
            return os;
        }
        std::ostream& operator()(std::ostream& os, mustache::verbatim const& v) const {
            return os << v.value;
        }
        std::ostream& operator()(std::ostream& os, mustache::variable const& v) const {
            return os << "{{" << v.value << "}}";
        }
        std::ostream& operator()(std::ostream& os, mustache::partial const& v) const {
            return os << "{{> " << v.value << "}}";
        }
        std::ostream& operator()(std::ostream& os, mustache::section const& v) const {
            os << "{{" << (v.sense?'#':'^') << v.control << "}}";
            (*this)(os, v.content);
            return os << "{{/" << v.control << "}}";
        }
    };
}

int main()
{
    std::cout << std::unitbuf;
    std::string input = "<ul>{{#time}}\n\t<li>{{> partial}}</li>{{/time}}</ul>\n "
        "<i>for all good men</i> to come to the {007} aid of "
        "their</bold> {{country}}. Result: {{^Res2}}(absent){{/Res2}}{{#Res2}}{{Res2}}{{/Res2}}"
        ;
    // Parser setup --------------------------------------------------------
    typedef std::string::const_iterator It;
    static const mustache_grammar<It> p;

    It first = input.begin(), last = input.end();

    try {
        mustache::sequence parsed_template;
        if (qi::parse(first, last, p, parsed_template))
            std::cout << "Parse success\n";
        else
            std::cout << "Parse failed\n";
        
        if (first != last)
            std::cout << "Remaing unparsed input: '" << std::string(first, last) << "'\n";

        std::cout << "Input:      " << input << "\n";
        std::cout << "Dump:       ";
        Dumping::dumper()(std::cout, parsed_template) << "\n";
    } catch(qi::expectation_failure<It> const& e)
    {
        std::cout << "Unexpected: '" << std::string(e.first, e.last) << "'\n";
    }
}

