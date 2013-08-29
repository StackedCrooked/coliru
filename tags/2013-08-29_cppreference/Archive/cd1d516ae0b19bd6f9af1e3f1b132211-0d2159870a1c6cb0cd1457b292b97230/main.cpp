#define BOOST_SPIRIT_DEBUG
#include <boost/spirit/include/qi.hpp>

#include <boost/fusion/adapted.hpp>
#include <boost/foreach.hpp>
#include <map>

// #include "txt.hpp"
// minimal mockup
namespace wc3lib { 
    using std::string;

    namespace map { namespace Txt { 
            typedef std::map<string, string> Pairs;

            struct Section
            {
                string name;
                Pairs entries;
            };

            typedef std::vector<Section> Sections;
    } }
}

// Only use in global namespace!
BOOST_FUSION_ADAPT_STRUCT(
    wc3lib::map::Txt::Section,
    (wc3lib::string, name)
    (wc3lib::map::Txt::Pairs, entries)
)

namespace wc3lib { namespace map { namespace client {

    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;

    /*
     * Doesn't skip eols since value pairs are separated linewise which therefore can be specified easier in the rules
     */
    template<typename Iterator>
    struct CommentSkipper : public qi::grammar<Iterator> {

        qi::rule<Iterator> skip;

        CommentSkipper() : CommentSkipper::base_type(skip, "PL/0")
        {
            using namespace qi;
            skip = ascii::blank | (lit("//") >> *(standard::char_ - eol) >> eol);

            BOOST_SPIRIT_DEBUG_NODES((skip));
        }
    };

    template <typename Iterator, typename Skipper = CommentSkipper<Iterator> >
    struct KeyValueSquence : qi::grammar<Iterator, Txt::Pairs(), Skipper>
    {
        qi::rule<Iterator, Txt::Pairs(), Skipper> pairs; // NOTE first rule used as parameter for base_type does always need the skipper type of the grammar
        qi::rule<Iterator, std::pair<string, string>(), Skipper> pair;
        qi::rule<Iterator, string()> key, value;

        KeyValueSquence() : KeyValueSquence::base_type(pairs)
        {
            using namespace qi;

            pairs = +pair; // use only > for backtracking
            pair  = +eol > key > lit('=') > value; // -('=' >> value)
            key   = standard::char_("a-zA-Z_") > *standard::char_("a-zA-Z_0-9");

            pair  = +eol >> key >> lit('=') >> value; // -('=' >> value)
            key   = standard::char_("a-zA-Z_") >> *standard::char_("a-zA-Z_0-9");

            value = *(standard::char_ - (eol|eoi)); // values can be empty or all characters except eol which indicates the end of the value

            BOOST_SPIRIT_DEBUG_NODES((pairs)(pair)(key)(value));
        }
    };

    template <typename Iterator, typename Skipper = CommentSkipper<Iterator> >
    struct SectionRule : qi::grammar<Iterator, Txt::Section(), Skipper>
    {
        qi::rule<Iterator, Txt::Section(), Skipper> query;
        qi::rule<Iterator, string()> name;

        KeyValueSquence<Iterator, Skipper> keyValueSequence;

        SectionRule() : SectionRule::base_type(query)
        {
            using namespace qi;

            name  =  lit('[') > standard::char_("a-zA-Z_") > *standard::char_("a-zA-Z_0-9") > lit(']');
            query =  name > -keyValueSequence;

            BOOST_SPIRIT_DEBUG_NODES((query)(name));
        }
    };

    template <typename Iterator>
    bool parse(Iterator first, Iterator last, Txt::Sections &sections)
    {
        SectionRule<Iterator> sectionGrammar;
        CommentSkipper<Iterator> commentSkipper;
        std::vector<Txt::Section> tmpSections;

        try
        {
            bool r = qi::phrase_parse(
                    first, last,
                    (sectionGrammar % +qi::eol) >> *qi::eol > qi::eoi,
                    // comment skipper
                    commentSkipper,
                    tmpSections //sections store into "sections"!
                    );

            if (first != last) // fail if we did not get a full match
            {
                std::cerr << "DEBUG: Unparsed: '" << std::string(first,last) << "\n";
                return false;
            }
            // TODO temporary workaround, add sections directly from heap to vector
            sections = tmpSections;

            return r;
        } catch(qi::expectation_failure<Iterator> const& e)
        {
            std::cerr << "Unexpected: " << e.what() << " at '" << std::string(e.first,e.last) << "\n";
            return false;
        }
    }

} } }

int main()
{
    std::cin.unsetf(std::ios::skipws);
    boost::spirit::istream_iterator f(std::cin), l;

    wc3lib::map::Txt::Sections parsed;
    bool ok = wc3lib::map::client::parse(f, l, parsed);
    if (ok)
    {
        std::cout << "Parsed " << parsed.size() << " sections\n";
        for(auto& section : parsed)
        {
            std::cout << "section [" << section.name << "] has " << section.entries.size() << " pairs\n";
        }
    }
}
