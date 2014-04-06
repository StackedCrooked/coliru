 #define BOOST_SPIRIT_LEXERTL_DEBUG
#define BOOST_SPIRIT_USE_PHOENIX_V3

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/lex_lexertl.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_statement.hpp>
#include <boost/spirit/include/phoenix_core.hpp>

#include <iostream>
#include <string>

using namespace boost::spirit; 
namespace phx=boost::phoenix;


///////////////////////////////////////////////////////////////////////////////
template <typename Lexer>
struct line_counter_with_comments : lex::lexer<Lexer>
{
    line_counter_with_comments()
      : line_counter_with_comments::base_type(lex::match_flags::match_default),line_no(0)
    {

        // The following tokens are associated with the default lexer state 
        // (the "INITIAL" state). Specifying 'INITIAL' as a lexer state is 
        // strictly optional.
            
        this->self = 
              lex::token_def<>("\n")[++phx::ref(line_no)]
            | lex::token_def<>("\\/\\/")[lex::_state="single_line_comment"]
            | lex::token_def<>(".")
            ;

        this->self("single_line_comment")
            = lex::token_def<>("\n")
            [ lex::_state="INITIAL",  ++phx::ref(line_no)]
            | lex::token_def<>(".")
            ;
    }
    
    int line_no;

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
    }
    return 0;
}

