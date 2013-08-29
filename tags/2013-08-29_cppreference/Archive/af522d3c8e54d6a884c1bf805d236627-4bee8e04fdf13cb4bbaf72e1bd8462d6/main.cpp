/**
 * Created on May 19, 2009
 * @author Stou Sandalski
 * This code is released in the public domain.
 * You can find the latest version on siafoo (http://www.siafoo.net/snippet/298)
 *
 * Updated to Spirit V2 - largely a rewrite by Seth Heeren April 2013
 */
#include <string>
#include <tuple>

#define BOOST_SPIRIT_DEBUG
#define BOOST_SPIRIT_USE_PHOENIX_V3
#define BOOST_RESULT_OF_USE_DECLTYPE

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/karma.hpp>

#include <boost/fusion/adapted/std_tuple.hpp> // mind include order https://svn.boost.org/trac/boost/ticket/8418
#include <boost/fusion/include/for_each.hpp>

namespace qi    = boost::spirit::qi;
namespace karma = boost::spirit::karma;
namespace phx   = boost::phoenix;

namespace CliParsing
{
    template <typename TVal=qi::unused_type> struct CliOption;

    template <> struct CliOption<qi::unused_type>
    {
        char sname;
        std::string lname, description;
    };

    using CliFlag = CliOption<qi::unused_type>;

    template <typename TVal>
    struct CliOption : CliFlag
    {
        CliOption(char sname, std::string lname, std::string description, TVal defaultvalue)
            : CliFlag { sname, lname, description },
              parsed(std::move(defaultvalue))
              { }
        //
        mutable TVal parsed;
    };

    template <typename TVal>
    CliOption<TVal> make_option(char sname, std::string lname, std::string description, TVal&& defaultvalue = TVal()) {
        return { sname, lname, description, std::forward<TVal>(defaultvalue) };
    }

    CliFlag make_option(char sname, std::string lname, std::string description) {
        return { sname, lname, description };
    }

    struct FormatUsageOption
    {
        std::ostream& operator()(std::ostream& output, CliFlag const& flag) const
        {
            assert(flag.sname || flag.lname.length());
            using namespace karma;
            if (flag.lname.empty())
                return output << format(
                        " -" << graph <<
                        (string("") << " (no description)" | eol << '\t' << string) <<
                        " (flag)",
                        flag.sname, flag.description) << "\n";
            else
                return output << format(
                        " --" << string <<
                        (" (-" << graph << ")" | eps) <<
                        (string("") << " (no description)" | eol << '\t' << string) <<
                        " (flag)",
                        flag.lname, flag.sname, flag.description) << "\n";
        }

        template <typename TVal>
        std::ostream& operator()(std::ostream& output, CliOption<TVal> const& option) const
        {
            assert(option.sname || option.lname.length());
            using namespace karma;
            if (option.lname.empty())
                return output << format(
                        " -" << graph <<
                        (string("") << " (no description)" | eol << '\t' << string) <<
                        (" (option with value; default '" << auto_ << "')"),
                        option.sname, option.description, option.parsed) << "\n";
            else
                return output << format(
                        " --" << string <<
                        (" (-" << graph << ")" | eps) <<
                        (string("") << " (no description)" | eol << '\t' << string) <<
                        (" (option with value; default '" << auto_ << "')"),
                        option.lname, option.sname, option.description, option.parsed) << "\n";
        }
    };

    template <typename Iterator>
    struct BuildOptionRule
    {
        qi::rule<Iterator> short_rule(CliFlag const& option) const {
            return qi::eps [ std::cout << phx::val("short form switch --") << option.lname << " parsed\n" ];
        }

        qi::rule<Iterator> long_rule(CliFlag const& option) const {
            return qi::eps [ std::cout << phx::val("long form switch --") << option.lname << " parsed\n" ];
        }

        template <typename TVal> qi::rule<Iterator> short_rule(CliOption<TVal> const& option) const {
            return qi::eps [ std::cout << phx::val("short form option --") << option.lname << " parsed\n" ];
        }

        template <typename TVal> qi::rule<Iterator> long_rule(CliOption<TVal> const& option) const {
            using namespace qi;
            return '=' >> qi::int_ [ 
                    phx::ref(option.parsed) = _1, 
                    std::cout << phx::val("long form option --") << option.lname << " parsed with value " << _1 << "\n" 
                ] //>> &lit('\0') [ std::cout << phx::val("terminator found\n") ]
                ;
        }
    };

    template <
        typename Iterator, 
        typename RuleBuilder = BuildOptionRule<Iterator>, 
        typename UsageFormatter = FormatUsageOption
        >
    struct OptionGrammar;

    template <typename Iterator, typename RuleBuilder, typename UsageFormatter>
    struct OptionGrammar : qi::grammar<Iterator>
    {
        template <typename... CliOptions>
        OptionGrammar(std::tuple<CliOptions...>& configuration) : OptionGrammar::base_type(start)
        {
            using namespace qi;
            using phx::arg_names::arg1;

            boost::fusion::for_each(configuration, BuildRules(*this));
            boost::fusion::for_each(configuration, FormatUsage(_usage));

            auto nul = char_('\0');

            start    = -argument % '\0';
            shortopt = shortNames [_a = _1] >> lazy(_a);
            longopt  = longNames  [_a = _1] >> lazy(_a);
            unparsed = as_string  [ +~nul ] [ std::cerr << phx::val("ignoring unparsed argument: '") << _1 << "'\n" ];
            argument = ('-' >> +shortopt) | ("--" >> longopt) >> -unparsed | unparsed;

            //BOOST_SPIRIT_DEBUG_NODES((start)(shortopt)(longopt)(unparsed)(argument));
        }

        std::string getUsage() const { return _usage.str(); }

      private:
        typedef qi::symbols<char,  qi::rule<Iterator>> symbols_t;
        symbols_t shortNames;
        symbols_t longNames;

        qi::rule<Iterator, qi::locals<qi::rule<Iterator>> > longopt, shortopt;
        qi::rule<Iterator> start, argument, unparsed;

        std::ostringstream _usage;

        struct BuildRules
        {
            BuildRules(OptionGrammar& grammarInstance) : _instance(grammarInstance) {}

            template <typename TVal> void operator()(CliOption<TVal>& current) const
            {
                assert(current.sname || current.lname.length());

                if (current.sname)
                    _instance.shortNames.add(std::string(1, current.sname), _builder.short_rule(current));

                if (!current.lname.empty())
                    _instance.longNames.add(current.lname, _builder.long_rule(current));
            }

          private:
            OptionGrammar& _instance;
            RuleBuilder    _builder;
        };

        struct FormatUsage
        {
            FormatUsage(std::ostream& output) : _output(output) {}

            template <typename TVal> void operator()(CliOption<TVal>& current) const
            {
                _output.clear(); // clear error flags
                if (!_formatter(_output, current))
                    std::cerr << "Warning: problem formatting usage information\n";
            }

          private:
            std::ostream&  _output;
            UsageFormatter _formatter;
        };
    };
}

int main(int argc, char* argv[])
{
    using CliParsing::make_option;

    typedef std::string::const_iterator It;

    auto config = std::make_tuple(
        make_option('a', "absolutely", "absolutely"),
        make_option('b', "borked"    , "borked")    ,
        make_option('c', "completion", "completion"),
        make_option('d', "debug",      "turn on debugging"),
        make_option('e', "",           "no long name")  ,
        //make_option('f', "flungeons" , "flungeons") ,
        //make_option('g', "goofing"   , "")   ,
        //make_option('m', "monitor",    "monitoring level"),
        make_option('t', "testing"   , "testing flags"),
        make_option('\0',"file"      , "with a filename (no short name)"),

        make_option('y', "assume-yes", "always assume yes"),
        make_option('v', "verbose",    "increase verbosity level"),
        make_option('i', "increment",  "stepsize to increment with", 5)
        );

    CliParsing::OptionGrammar<It> parser(config);

    using namespace phx::arg_names;
    const auto cmdline = std::accumulate(argv+1, argv+argc, std::string(), arg1 + arg2 + '\0');

    bool ok = qi::parse(begin(cmdline), end(cmdline), parser);

    std::cout << "Parse success " << std::boolalpha << ok << "\n";
    std::cout << parser.getUsage();

    return ok? 0 : 255;
}
