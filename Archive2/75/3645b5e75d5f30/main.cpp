//#define BOOST_SPIRIT_LEXERTL_DEBUG
#define BOOST_SPIRIT_USE_PHOENIX_V3

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/lex_lexertl.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_statement.hpp>
#include <boost/spirit/include/phoenix_function.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/fusion/include/vector.hpp>

#include <iostream>
#include <string>

namespace lex= boost::spirit::lex; 
namespace phx=boost::phoenix;

void end_comment()
{
    std::cout << "... and then it ends." << std::endl;
}

BOOST_PHOENIX_ADAPT_FUNCTION_NULLARY(void,end_comment_,end_comment);

template <typename String,typename Context>
void set_lexer_state(const String& state, Context& ctx)
{
    ctx.set_state_name(state);
}

BOOST_PHOENIX_ADAPT_FUNCTION(void,set_lexer_state_, set_lexer_state,2);

struct new_line
{
    typedef void result_type;
    
    void operator()() const
    {
        std::cout << std::endl;
    }
};

BOOST_PHOENIX_ADAPT_CALLABLE_NULLARY(new_line_,new_line);

struct token_printer
{
    template <typename Sig>
    struct result;
    
    template <typename This, typename Iterator>
    struct result<This(Iterator,Iterator)>
    {
        typedef void type;
    };
    
    template <typename Iterator>
    void operator()(Iterator begin, Iterator end) const
    {
        std::cout << std::string(begin,end);
    }
};

BOOST_PHOENIX_ADAPT_CALLABLE(token_printer_,token_printer,2);

struct char_counter
{
    template <typename Sig>
    struct result;
    
    template <typename This, typename Count>
    struct result<This(Count)>
    {
        typedef void type;
    };
    
    template <typename Count>
    void operator()(Count& count) const
    {
        ++count;
    }
};

phx::function<char_counter> char_counter_=char_counter();



///////////////////////////////////////////////////////////////////////////////
template <typename Lexer>
struct line_counter_with_comments : lex::lexer<Lexer>
{
    line_counter_with_comments()
      : line_counter_with_comments::base_type(lex::match_flags::match_default),line_no(0),char_no(0)
    {

        // The following tokens are associated with the default lexer state 
        // (the "INITIAL" state). Specifying 'INITIAL' as a lexer state is 
        // strictly optional.
        
        phx::arg_names::_5_type _ctx; //this allows phoenix to access the context
            
        this->self = 
              lex::token_def<>("\n")[++phx::ref(line_no), new_line_()]
            | lex::token_def<>("\\/\\/")[set_lexer_state_("single_line_comment",_ctx), std::cout << phx::val("A comment starts...") << std::endl]
            | lex::token_def<>(".")[token_printer_(lex::_start,lex::_end),char_counter_(phx::ref(char_no))]
            ;

        this->self("single_line_comment")
            = lex::token_def<>("\n")
            [
                set_lexer_state_("INITIAL",_ctx),
                ++phx::ref(line_no),
                end_comment_()
            ]
            | lex::token_def<>(".")
            ;
    }
    
    int line_no;
    int char_no;

};

  ///////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
    // iterator type used to expose the underlying input stream
    typedef std::string::iterator base_iterator_type;

    // lexer type
    typedef 
        lex::lexertl::actor_lexer<lex::lexertl::token<base_iterator_type> > 
    lexer_type;

    // now we use the types defined above to create the lexer and grammar
    // object instances needed to invoke the parsing process
    line_counter_with_comments<lexer_type> line_counter;             // Our lexer

    // No parsing is done alltogether, everything happens in the lexer semantic
    // actions.
    std::string str (
        "line1;\n"
        "//line2;\n"
        "line3;\n"
    );
    base_iterator_type first = str.begin();
    bool r = lex::tokenize(first, str.end(), line_counter);

    if (!r) {
        std::string rest(first, str.end());
        std::cerr << "Lexical analysis failed\n" << "stopped at: \"" 
                  << rest << "\"\n";
    }
    else
    {
        std::cout << "There were " << line_counter.line_no << " lines." << std::endl;
        std::cout << "There were " << line_counter.char_no << " characters outside of comments." << std::endl;
    }
    return 0;
}

