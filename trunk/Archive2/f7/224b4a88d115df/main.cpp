#define BOOST_SPIRIT_DEBUG
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/lex_lexertl.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
 
namespace qi = boost::spirit::qi;
namespace lex = boost::spirit::lex;
 
// my grammar replacing int_
template<typename Iterator, typename Skipper=qi::space_type>
struct my_int : qi::grammar<Iterator, int(), Skipper>
{
    template<typename ... Args>
    my_int(Args&... args):my_int(args...,0)
    {
        //You put everything that is common here
        BOOST_SPIRIT_DEBUG_NODE(start);
    }
     
    template<typename TokenDef>
    my_int(TokenDef &tok,int):my_int::base_type(start)
    {
        start %= tok.integer_;
    }
    
    my_int(int):my_int::base_type(start)
    {
        start %= qi::int_;
    }
    qi::rule<Iterator, int(), Skipper> start;

};
 
// grammar
 
template<typename Iterator, typename Skipper=qi::space_type>
struct my_list : qi::grammar<Iterator, std::vector<int>(), Skipper>
{
    template<typename ... Args>
    my_list(Args&... args): my_list::base_type(start),expr(args...)
    {
        start %= expr % ',';
         
        BOOST_SPIRIT_DEBUG_NODE(start);
    }
    
    my_int<Iterator, Skipper> expr;
    qi::rule<Iterator, std::vector<int>(), Skipper> start;
};
 
template <typename Lexer>
struct Tokens: lex::lexer<Lexer>
{
public:
    Tokens()
    {
        using lex::_pass;
        using lex::_tokenid;
        using lex::_start;
         
        whitespace_ = "\\s+";
        integer_    = "\\d+";
        char_	= ".";
         
        this->self = whitespace_ [_pass = lex::pass_flags::pass_ignore]
        | integer_
        | char_ [_tokenid = *_start]
        ;
    }
        
    lex::token_def<int>	integer_;
    lex::token_def<int> char_;
    lex::token_def<> whitespace_;
};
 
// send vec of tokens to ostream
template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
    for (auto& e : v)
    {
        os << std::hex << e;
        if (isprint(e)) { os << "[" << static_cast<char>(e) << "] "; }
        os << ", ";
    }
    return os;
}
 
int main()
{
    for (auto& input : std::list<std::string> {
        "1, 2;",
        "3, 4, 5;"
        }
    ) 
    {
        std::cout << "input: " << input << std::endl;
         
        {
            std::vector<int> result;
    
            // just use qi parsers
            auto first(std::begin(input)), last(std::end(input));
            my_list<decltype(first)> p;
            bool ok = qi::phrase_parse(first, last, p > ';', qi::space, result);
            std::string unparsed(first, last);
            if (!ok)
                std::cout << "invalid input\n";
            else
                std::cout << "result: " << result << std::endl;
             
            if (first != last)
                std::cout << "unparsed: '" << unparsed << std::endl;
        }
        
        {
            std::vector<int> result;

            // use a spirit lexer
            using token_type = lex::lexertl::token<char const *, boost::mpl::vector<int, std::string>>;
            using lexer_type = lex::lexertl::actor_lexer<token_type>;
             
            Tokens<lexer_type> my_lexer;
            const char *f = input.c_str();
            const char *l = &f[input.size()];
            auto first = my_lexer.begin(f, l);
            auto last = my_lexer.end();
            my_list<decltype(first), qi::unused_type> p(my_lexer);
            bool ok = qi::parse(first, last, p > ';', result);
            std::vector<token_type> unparsed(first, last);
             
            if (!ok)
                std::cout << "invalid input\n";
            else
                std::cout << "result: " << result << std::endl;
             
            if (first != last)
                std::cout << "unparsed: '" << unparsed << std::endl; 
        }
    }
 
    return 0;
}