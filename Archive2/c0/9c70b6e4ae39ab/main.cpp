//#define BOOST_SPIRIT_DEBUG
#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/fusion/adapted/struct.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/utility/string_ref.hpp>
#include <functional>
#include <map>

namespace moustache {

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

BOOST_FUSION_ADAPT_STRUCT(moustache::section, (bool, sense)(boost::string_ref, control)(moustache::sequence, content))

namespace qi = boost::spirit::qi;
namespace phx= boost::phoenix;

template <typename Iterator>
    struct moustache_grammar : qi::grammar<Iterator, moustache::sequence()>
{
    moustache_grammar() : moustache_grammar::base_type(sequence)
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
    qi::rule<Iterator, moustache::sequence()> sequence;
    qi::rule<Iterator, moustache::melement()> element;
    qi::rule<Iterator, moustache::partial()>  partial;
    qi::rule<Iterator, moustache::section(), qi::locals<std::string> >  section;
    qi::rule<Iterator, bool()>                sense;                  // postive  or negative
    qi::rule<Iterator, moustache::variable()> variable;
    qi::rule<Iterator, moustache::verbatim()> verbatim;
    qi::rule<Iterator, boost::string_ref()>   reference;
};

namespace Dumping {
    struct dumper : boost::static_visitor<std::ostream&>
    {
        std::ostream& operator()(std::ostream& os, moustache::sequence const& v) const {
            for(auto& element : v)
                boost::apply_visitor(std::bind(dumper(), std::ref(os), std::placeholders::_1), element);
            return os;
        }
        std::ostream& operator()(std::ostream& os, moustache::verbatim const& v) const {
            return os << v.value;
        }
        std::ostream& operator()(std::ostream& os, moustache::variable const& v) const {
            return os << "{{" << v.value << "}}";
        }
        std::ostream& operator()(std::ostream& os, moustache::partial const& v) const {
            return os << "{{> " << v.value << "}}";
        }
        std::ostream& operator()(std::ostream& os, moustache::section const& v) const {
            os << "{{" << (v.sense?'#':'^') << v.control << "}}";
            (*this)(os, v.content);
            return os << "{{/" << v.control << "}}";
        }
    };
}

namespace ContextExpander {

    struct Nil { };

    using Value = boost::make_recursive_variant<
        Nil,
        double,
        std::string,
        std::map<std::string, boost::recursive_variant_>,
        std::vector<boost::recursive_variant_>
    >::type;

    using Dict  = std::map<std::string, Value>;
    using Array = std::vector<Value>;

    static inline std::ostream& operator<<(std::ostream& os, Nil   const&)   { return os << "#NIL#"; }
    static inline std::ostream& operator<<(std::ostream& os, Dict  const& v) { return os << "#DICT("  << v.size() << ")#"; }
    static inline std::ostream& operator<<(std::ostream& os, Array const& v) { return os << "#ARRAY(" << v.size() << ")#"; }

    struct expander : boost::static_visitor<std::ostream&>
    {
        std::ostream& operator()(std::ostream& os, Value const& ctx, moustache::sequence const& v) const {
            for(auto& element : v)
                boost::apply_visitor(std::bind(expander(), std::ref(os), std::placeholders::_1, std::placeholders::_2), ctx, element);
            return os;
        }

        template <typename Ctx>
        std::ostream& operator()(std::ostream& os, Ctx const&/*ignored*/, moustache::verbatim const& v) const {
            return os << v.value;
        }

        std::ostream& operator()(std::ostream& os, Dict const& ctx, moustache::variable const& v) const {
            auto it = ctx.find(v.value.to_string());
            if (it != ctx.end())
                os << it->second;
            return os;
        }

        template <typename Ctx>
        std::ostream& operator()(std::ostream& os, Ctx const&, moustache::variable const&) const {
            return os;
        }

        std::ostream& operator()(std::ostream& os, Dict const& ctx, moustache::partial const& v) const {
            auto it = ctx.find(v.value.to_string());
            if (it != ctx.end())
            {
                static const moustache_grammar<std::string::const_iterator> p;

                auto const& subtemplate = boost::get<std::string>(it->second);
                std::string::const_iterator first = subtemplate.begin(), last = subtemplate.end();

                moustache::sequence dynamic_template;
                if (qi::parse(first, last, p, dynamic_template))
                    return (*this)(os, Value{ctx}, dynamic_template);
            }
            return os << "#ERROR#";
        }

        std::ostream& operator()(std::ostream& os, Dict const& ctx, moustache::section const& v) const {
            auto it = ctx.find(v.control.to_string());
            if (it != ctx.end())
                boost::apply_visitor(std::bind(do_section(), std::ref(os), std::placeholders::_1, std::cref(v)), it->second);
            else if (!v.sense)
                (*this)(os, Value{/*Nil*/}, v.content);

            return os;
        }

        template <typename Ctx, typename T>
        std::ostream& operator()(std::ostream& os, Ctx const&/* ctx*/, T const&/* element*/) const {
            return os << "[TBI:" << __PRETTY_FUNCTION__ << "]";
        }

      private:
        struct do_section : boost::static_visitor<> {
            void operator()(std::ostream& os, Array const& ctx, moustache::section const& v) const {
                for(auto& item : ctx)
                    expander()(os, item, v.content);
            }
            template <typename Ctx>
            void operator()(std::ostream& os, Ctx const& ctx, moustache::section const& v) const {
                if (v.sense == truthiness(ctx))
                    expander()(os, Value(ctx), v.content);
            }
          private:
            static bool truthiness(Nil)                              { return false; }
            static bool truthiness(double d)                         { return 0. == d; }
            template <typename T> static bool truthiness(T const& v) { return !v.empty(); }
        };
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
    static const moustache_grammar<It> p;

    It first = input.begin(), last = input.end();

    try {
        moustache::sequence parsed_template;
        if (qi::parse(first, last, p, parsed_template))
        {
            std::cout << "Parse success\n";
        } else
        {
            std::cout << "Parse failed\n";
        }
        
        if (first != last)
        {
            std::cout << "Remaing unparsed input: '" << std::string(first, last) << "'\n";
        }

        std::cout << "Input:      " << input << "\n";
        std::cout << "Dump:       ";
        Dumping::dumper()(std::cout, parsed_template) << "\n";

        std::cout << "Evaluation: ";

        {
            using namespace ContextExpander;
            expander engine;

            Value const ctx = Dict { 
                { "time", Array {
                    Dict { { "partial", "gugus {{zeit}} (a.k.a. <u>{{title}}</u>)"},             { "title", "noon" },    { "zeit", "12:00" } },
                    Dict { { "partial", "gugus {{zeit}} (a.k.a. <u>{{title}}</u>)"},             { "title", "evening" }, { "zeit", "19:30" } },
                    Dict { { "partial", "gugus <u>{{title}}</u> (expected at around {{zeit}})"}, { "title", "dawn" },    { "zeit", "06:00" } },
                } },
                { "country", "ESP" },
                { "Res3", "unused" }
            };

            engine(std::cout, ctx, parsed_template);
        }
    } catch(qi::expectation_failure<It> const& e)
    {
        std::cout << "Unexpected: '" << std::string(e.first, e.last) << "'\n";
    }
}
