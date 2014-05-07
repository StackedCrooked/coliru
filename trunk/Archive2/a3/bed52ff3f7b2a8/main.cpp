//#define BOOST_SPIRIT_DEBUG
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace qi = boost::spirit::qi;
namespace phx= boost::phoenix;
namespace fsn= boost::fusion;

namespace
{
    #define SUPPORT_ESCAPES

    static bool process(std::string& macro)
    {
        if (macro == "error") {
            return false; // fail the parse
        }

        if (macro == "hello") {
            macro = "bye";
        } else if (macro == "bye") {
            macro = "We meet again";
        } else if (macro == "sideeffect") {
            std::cerr << "this is a side effect while parsing\n";
            macro = "(done)";
        } else if (std::string::npos != macro.find('~')) {  
            std::reverse(macro.begin(), macro.end());
            macro.erase(std::remove(macro.begin(), macro.end(), '~'));
        } else {
            macro = std::string("${") + macro + "}"; // this makes the unsupported macros appear unchanged
        }

        return true;
    }

    template<typename Iterator, typename OutIt>
        struct skel_grammar : public qi::grammar<Iterator>
    {
        struct fastfwd {
            template<typename,typename> struct result { typedef bool type; };

            template<typename R, typename O> 
                bool operator()(const R&r,O& o) const
            {
#ifndef SUPPORT_ESCAPES
                o = std::copy(r.begin(),r.end(),o);
#else
                auto f = std::begin(r), l = std::end(r);
                while(f!=l)
                {
                    if (('\\'==*f) && (l == ++f))
                        break;
                    *o++ = *f++;
                }
#endif
                return true; // false to fail the parse
            }
        } copy;

        skel_grammar(OutIt& out) : skel_grammar::base_type(start)
        {
            using namespace qi;

#ifdef SUPPORT_ESCAPES
            rawch = ('\\' >> char_) | char_;
#else
#           define rawch qi::char_
#endif

            macro = ("${" >> (
                           (*(rawch - "}" - "${") [ _val += _1 ]) 
                         % macro                   [ _val += _1 ] // allow nests
                      ) >> 
                      "}")  
                [ _pass = phx::bind(process, _val) ];

            start = 
                raw [ +(rawch - "${") ] [ _pass = phx::bind(copy, _1, phx::ref(out)) ] 
              % macro                   [ _pass = phx::bind(copy, _1, phx::ref(out)) ]
              ;

            BOOST_SPIRIT_DEBUG_NODE(start);
            BOOST_SPIRIT_DEBUG_NODE(macro);

#           undef rawch
        }

        private:
#ifdef SUPPORT_ESCAPES
        qi::rule<Iterator, char()> rawch;
#endif
        qi::rule<Iterator, std::string()> macro;
        qi::rule<Iterator> start;
    };
}

int main(int argc, char* argv[])
{
    std::string input = 
        "Greeting is ${hello} world!\n"
        "Side effects are ${sideeffect} and ${other} vars are untouched\n"
        "Empty ${} macros are ok, as are stray '}' characters.\n"
        "${nested ${macros} (${hello}?) work}\n"
        "The order of expansion (evaluation) is _eager_: '${${hello}}' will expand to the same as '${bye}'\n"
        "Lastly you can do algorithmic stuff too: ${!esrever ~ni ${hello}}\n"
#ifdef SUPPORT_ESCAPES // bonus: escapes
        "You can escape \\${hello} (not expanded to '${hello}')\n"
        "Demonstrate how it ${avoids $\\{nesting\\} macros}.\n"
#endif
        ;

    std::ostringstream oss;
    std::ostream_iterator<char> out(oss);

    skel_grammar<std::string::iterator, std::ostream_iterator<char> > grammar(out);

    std::string::iterator f(input.begin()), l(input.end());
    bool r = qi::parse(f, l, grammar);

    std::cout << "parse result: " << (r?"success":"failure") << "\n";
    if (f!=l)
        std::cout << "unparsed remaining: '" << std::string(f,l) << "'\n";

    std::cout << "Streamed output:\n\n" << oss.str() << '\n';

    return 0;
}
