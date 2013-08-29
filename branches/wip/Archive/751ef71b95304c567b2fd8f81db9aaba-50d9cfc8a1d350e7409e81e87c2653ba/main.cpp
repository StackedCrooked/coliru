//#include <boost/config/warning_disable.hpp>
//#define BOOST_SPIRIT_DEBUG_PRINT_SOME 80
//#define BOOST_SPIRIT_DEBUG // before including Spirit
#include <boost/spirit/include/lex_lexertl.hpp>
#include <boost/spirit/include/qi.hpp>
#include <fstream>
#ifdef MEMORY_MAPPED
#   include <boost/iostreams/device/mapped_file.hpp>
#endif
//#include <boost/spirit/include/lex_generate_static_lexertl.hpp>

namespace /*anon*/
{
    namespace phx=boost::phoenix;
    namespace qi =boost::spirit::qi;
    namespace lex=boost::spirit::lex;

    static bool undoublequote(std::string& val)
    {
        auto outidx = 0;
        for(auto in = val.begin(); in!=val.end(); ++in) {
            switch(*in) {
                case '"': 
                    if (++in == val.end()) { // eat the escape
                        // end of input reached
                        val.resize(outidx); // resize to effective chars
                        return true;
                    }
                    // fall through
                default:
                    val[outidx++] = *in; // append the character
            }
        }

        return false; // not ended with double quote as expected
    }

    template <typename Lexer>
        struct mylexer_t : lex::lexer<Lexer>
    {
        struct undoublequote_lex_type {
            template <typename, typename, typename, typename> struct result { typedef void type; };

            template <typename It, typename IdType, typename pass_flag, typename Ctx>
                void operator()(It& f, It& l, pass_flag& pass, IdType& id, Ctx& ctx) const {
                    std::string raw(f,l);
                    if (undoublequote(raw))
                        ctx.set_value(raw);
                    else
                        pass = lex::pass_flags::pass_fail;
                }
        } undoublequote_lex;

        mylexer_t()
        {
            string_quote_double = "\\\"([^\"]|\\\"\\\")*\\\"";

            const static undoublequote_lex_type undoublequote_lex;
            this->self("INITIAL")
                = string_quote_double [ undoublequote_lex ]
                | lex::token_def<>("[ \t\r\n]") [ lex::_pass = lex::pass_flags::pass_ignore ]
                ;
        }

        lex::token_def<std::string> string_quote_double;
    };

    template <typename Iterator> struct mygrammar_t
        : public qi::grammar<Iterator, std::vector<std::string>()>
    {
        typedef mygrammar_t<Iterator> This;

        template <typename TokenDef>
            mygrammar_t(TokenDef const& tok) : mygrammar_t::base_type(start)
        {
            using namespace qi;

            string_quote_double = tok.string_quote_double;
            start = *string_quote_double;

            BOOST_SPIRIT_DEBUG_NODES((start)(string_quote_double));
        }

      private:
        qi::rule<Iterator, std::vector<std::string>()> start;
        qi::rule<Iterator, std::string()> string_quote_double;
    };
}

std::vector<std::string> do_test_parse(const std::string& v)
{
    char const *first = &v[0];
    char const *last = first+v.size();

    typedef lex::lexertl::token<char const*, boost::mpl::vector<char, std::string> > token_type;
    typedef lex::lexertl::actor_lexer<token_type> lexer_type;

    typedef mylexer_t<lexer_type>::iterator_type iterator_type;
    const static mylexer_t<lexer_type> mylexer;
    const static mygrammar_t<iterator_type> parser(mylexer);

    auto iter = mylexer.begin(first, last);
    auto end = mylexer.end();

    std::vector<std::string> data;
    bool r = qi::parse(iter, end, parser, data);

    r = r && (iter == end);

    if (!r)
        std::cerr << "parsing (" << iter->state() << ") failed at: '" << std::string(first, last) << "'\n";

    return data;
}

int main(int argc, const char *argv[])
{
    for (auto&& s : do_test_parse( "\"bla\"\"blo\""))
        std::cout << s << std::endl;
}
