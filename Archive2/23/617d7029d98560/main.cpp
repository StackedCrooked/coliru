#include <boost/spirit/include/lex_lexertl.hpp>
#include <boost/spirit/include/qi.hpp>
#include <fstream>
#ifdef MEMORY_MAPPED
#   include <boost/iostreams/device/mapped_file.hpp>
#endif

namespace /*anon*/
{
    namespace qi =boost::spirit::qi;
    namespace lex=boost::spirit::lex;

    template <typename Lexer>
        struct mylexer_t : lex::lexer<Lexer>
    {
        mylexer_t()
        {
            fileheader = "hello";

            this->self = fileheader
                | space [ lex::_pass = lex::pass_flags::pass_ignore ];
        }

        lex::token_def<lex::omit>
            fileheader, space;
    };

    template <typename Iterator> struct my_grammar_t
        : public qi::grammar<Iterator>
    {
        template <typename TokenDef>
            my_grammar_t(TokenDef const& tok) 
                : my_grammar_t::base_type(header)
        {
            header = tok.fileheader;
            BOOST_SPIRIT_DEBUG_NODE(header);
        }

      private:
        qi::rule<Iterator> header;
    };
}

namespace /* */ {

    std::string safechar(char ch) {
        switch (ch) {
            case '\t': return "\\t"; break;
            case '\0': return "\\0"; break;
            case '\r': return "\\r"; break;
            case '\n': return "\\n"; break;
        }
        return std::string(1, ch); 
    }

    template <typename It>
        std::string showtoken(const boost::iterator_range<It>& range)
        {
            std::ostringstream oss;
            oss << '[';
            std::transform(range.begin(), range.end(), std::ostream_iterator<std::string>(oss), safechar);
            oss << ']';
            return oss.str();
        }
}

bool parsefile(const std::string& spec)
{
#ifdef MEMORY_MAPPED
    typedef char const* It;
    boost::iostreams::mapped_file mmap(spec.c_str(), boost::iostreams::mapped_file::readonly);
    char const *first = mmap.const_data();
    char const *last = first + mmap.size();
#else
    typedef char const* It;
    std::ifstream in(spec.c_str());
    in.unsetf(std::ios::skipws);

    std::string v(std::istreambuf_iterator<char>(in.rdbuf()), std::istreambuf_iterator<char>());
    It first = &v[0];
    It last = first+v.size();
#endif

    typedef lex::lexertl::token<It  /*, boost::mpl::vector<char, unsigned int, std::string> */> token_type;
    typedef lex::lexertl::actor_lexer<token_type> lexer_type;

    typedef mylexer_t<lexer_type>::iterator_type iterator_type;
    try
    {
        static mylexer_t<lexer_type> mylexer;
        static my_grammar_t<iterator_type> parser(mylexer);

        auto iter = mylexer.begin(first, last);
        auto end  = mylexer.end();

        bool r = qi::parse(iter, end, parser);

        r = r && (iter == end);

        if (!r)
            std::cerr << spec << ": parsing failed at: \"" << std::string(first, last) << "\"\n";
        return r;
    }
    catch (const qi::expectation_failure<iterator_type>& e)
    {
        std::cerr << "FIXME: expected " << e.what_ << ", got '";
        for (auto it=e.first; it!=e.last; it++)
            std::cerr << showtoken(it->value());
        std::cerr << "'" << std::endl;
        return false;
    }
}

int main()
{
    if (parsefile("input.bin"))
        return 0;
    return 1;
}

