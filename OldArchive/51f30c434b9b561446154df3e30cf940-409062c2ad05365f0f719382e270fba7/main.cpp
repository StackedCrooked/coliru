//#define BOOST_SPIRIT_QI_DEBUG
//#define STATE_WS

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/lex_lexertl.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/std_pair.hpp> 

#include <boost/algorithm/string.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/lexical_cast.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <utility>

namespace bs  = boost::spirit;
namespace lex = boost::spirit::lex;
namespace qi  = boost::spirit::qi;
namespace phx = boost::phoenix;

// Token definition base, defines all tokens for the base grammar below
template <typename Lexer>
struct sql_tokens : lex::lexer<Lexer>
{
public:
    // Tokens with no attributes.
    lex::token_def<lex::omit> type_smallint;
    lex::token_def<lex::omit> type_int;
    lex::token_def<lex::omit> type_varchar;
    lex::token_def<lex::omit> type_text;
    lex::token_def<lex::omit> type_date;
    lex::token_def<lex::omit> kw_not_null;
    lex::token_def<lex::omit> kw_auto_increment;
    lex::token_def<lex::omit> kw_unique;
    lex::token_def<lex::omit> kw_default;
    lex::token_def<lex::omit> kw_create;
    lex::token_def<lex::omit> kw_table;
    lex::token_def<lex::omit> kw_constraint;
    lex::token_def<lex::omit> kw_primary_key;

    // Attributed tokens. (If you add a new type, don't forget to add it to the lex::lexertl::token definition too).
    lex::token_def<int>         signed_digit;
    lex::token_def<std::size_t> unsigned_digit;
    lex::token_def<std::string> identifier;
    lex::token_def<std::string> quoted_string;

    lex::token_def<lex::omit>   ws, comment, cstyle_comment;

    sql_tokens()
    {
        // Column data types.
        type_smallint     = "(?i:smallint)";
        type_int          = "(?i:int)";
        type_varchar      = "(?i:varchar)";
        type_text         = "(?i:text)";
        type_date         = "(?i:date)";

        // Keywords.
        kw_not_null       = "(?i:not +null)";
        kw_auto_increment = "(?i:auto_increment)";
        kw_unique         = "(?i:unique)";
        kw_default        = "(?i:default)";
        kw_create         = "(?i:create)";
        kw_table          = "(?i:table)";
        kw_constraint     = "(?i:constraint)";
        kw_primary_key    = "(?i:primary +key)";

        // Values.
        signed_digit      = "[+-]?[0-9]+";
        unsigned_digit    = "[0-9]+";
        quoted_string     = "\\\"(\\\\.|[^\\\"])*\\\""; // \"(\\.|[^\"])*\"

        // Identifier.
        identifier        = "[a-zA-Z][a-zA-Z0-9_]*";

        // The token must be added in priority order.
        this->self += lex::token_def<>('(') | ')' | ',' | ';';
        this->self += type_smallint | type_int | type_varchar | type_text |
                                    type_date;
        this->self += kw_not_null | kw_auto_increment | kw_unique | kw_default |
                                    kw_create | kw_table | kw_constraint | kw_primary_key;
        this->self += identifier | unsigned_digit | signed_digit | quoted_string;

#ifdef STATE_WS
        // define the whitespace to ignore.
        this->self("WS")
                =       ws
                |       comment
                |       cstyle_comment
                ;
#else
        ws = "[ \\t\\n]+";
        comment = "--[^\\n]*\\n";  // Single line comments with --
        cstyle_comment = "\\/\\*[^*]*\\*+([^/*][^*]*\\*+)*\\/"; // C-style comments

        this->self += ws              [ lex::_pass = lex::pass_flags::pass_ignore ] 
                    | comment         [ lex::_pass = lex::pass_flags::pass_ignore ]
                    | cstyle_comment  [ lex::_pass = lex::pass_flags::pass_ignore ]
                    ;
#endif
    }
};

// Grammar definition, define a little part of the SQL language.
template <typename Iterator, typename Lexer>
struct sql_grammar 
#ifdef STATE_WS
    : qi::grammar<Iterator, qi::in_state_skipper<Lexer> >
#else
    : qi::grammar<Iterator>
#endif
{
    template <typename TokenDef>
    sql_grammar(TokenDef const& tok)
        : sql_grammar::base_type(program, "program")
    {
        program 
            =  (statement % ';') >> *qi::lit(';')
            ;

        statement 
            =   create_statement.alias()
            ;

        create_statement
            =   tok.kw_create >> create_table
            ;

        create_table
            =   tok.kw_table >> tok.identifier >> '(' >> create_table_columns >> -(',' >> table_constraints) >> ')'
            ;

        table_constraints
            =   constraint_definition % ','
            ;

        constraint_definition
            = tok.kw_constraint >> tok.identifier >> primary_key_constraint
            ;

        primary_key_constraint
            = tok.kw_primary_key >> '(' >> (tok.identifier % ',') >> ')'
            ;

        create_table_columns
            =   column_definition % ','
            ;

        column_definition
            =   tok.identifier >> column_type >> *type_constraint
            ;

        type_constraint
            =   tok.kw_not_null
            |   tok.kw_auto_increment
            |   tok.kw_unique
            |   default_value
            ;

        default_value
            =   tok.kw_default > tok.quoted_string
            ;

        column_type
            =   tok.type_smallint
            |   tok.type_int
            |   (tok.type_varchar > '(' > tok.unsigned_digit > ')') 
            |   tok.type_text
            |   tok.type_date
            ;

        program.name("program");
        statement.name("statement");
        create_statement.name("create statement");
        create_table.name("create table");
        create_table_columns.name("create table columns");
        column_definition.name("column definition");
        column_type.name("column type");
        default_value.name("default value");
        type_constraint.name("type constraint");
        table_constraints.name("table constraints");
        constraint_definition.name("constraint definition");
        primary_key_constraint.name("primary key constraint");

        BOOST_SPIRIT_DEBUG_NODE(program);
        BOOST_SPIRIT_DEBUG_NODE(statement);
        BOOST_SPIRIT_DEBUG_NODE(create_statement);
        BOOST_SPIRIT_DEBUG_NODE(create_table);
        BOOST_SPIRIT_DEBUG_NODE(create_table_columns);
        BOOST_SPIRIT_DEBUG_NODE(column_definition);
        BOOST_SPIRIT_DEBUG_NODE(column_type);
        BOOST_SPIRIT_DEBUG_NODE(default_value);
        BOOST_SPIRIT_DEBUG_NODE(type_constraint);
        BOOST_SPIRIT_DEBUG_NODE(table_constraints);
        BOOST_SPIRIT_DEBUG_NODE(constraint_definition);
        BOOST_SPIRIT_DEBUG_NODE(primary_key_constraint);

        using namespace qi::labels;
        qi::on_error<qi::fail>
        (
            program,
            std::cout
                << phx::val("Error! Expecting ")
                << bs::_4                               // what failed?
                << phx::val(" here: \"")
                << phx::construct<std::string>(bs::_3, bs::_2)   // iterators to error-pos, end
                << phx::val("\"")
                << std::endl
        );
    }

private:
#ifdef STATE_WS
    typedef qi::in_state_skipper<Lexer> skipper_type;
#else
    typedef qi::unused_type skipper_type;
#endif
    typedef qi::rule<Iterator, skipper_type> simple_rule;

    simple_rule program, statement, create_statement, create_table, table_constraints, constraint_definition;
    simple_rule primary_key_constraint, create_table_columns, column_definition, type_constraint, default_value, column_type;
};

std::string cin2string()
{
    std::istreambuf_iterator<char> f(std::cin), l;
    std::string result;
    std::copy(f, l, std::back_inserter(result));
    return result;
}

int main(int argc, char* argv[])
{
    // iterator type used to expose the underlying input stream
    typedef std::string::const_iterator base_iterator_type;

    // This is the lexer token type to use.
    typedef lex::lexertl::token<
        base_iterator_type, boost::mpl::vector<int, std::size_t, std::string> 
    > token_type;

    // Here we use the lexertl based lexer engine.
    typedef lex::lexertl::actor_lexer<token_type> lexer_type;

    // This is the token definition type (derived from the given lexer type).
    typedef sql_tokens<lexer_type> sql_tokens;

    // this is the iterator type exposed by the lexer 
    typedef sql_tokens::iterator_type iterator_type;

    // this is the type of the grammar to parse
    typedef sql_grammar<iterator_type, sql_tokens::lexer_def> sql_grammar;

    // now we use the types defined above to create the lexer and grammar
    // object instances needed to invoke the parsing process
    sql_tokens tokens;                         // Our lexer
    sql_grammar sql(tokens);                  // Our parser

    const std::string str = cin2string();

    // At this point we generate the iterator pair used to expose the
    // tokenized input stream.
    base_iterator_type it = str.begin();
    iterator_type iter = tokens.begin(it, str.end());
    iterator_type end = tokens.end();

    // Parsing is done based on the the token stream, not the character 
    // stream read from the input.
    // Note how we use the lexer defined above as the skip parser. It must
    // be explicitly wrapped inside a state directive, switching the lexer 
    // state for the duration of skipping whitespace.
#ifdef STATE_WS
    std::string ws("WS");
    bool r = qi::phrase_parse(iter, end, sql, qi::in_state(ws)[tokens.self]);
#else
    bool r = qi::parse(iter, end, sql);
#endif

    if (r && iter == end)
    {
        std::cout << "-------------------------\n";
        std::cout << "Parsing succeeded\n";
        std::cout << "-------------------------\n";
    }
    else
    {
        std::cout << "-------------------------\n";
        std::cout << "Parsing failed\n";
        std::cout << "-------------------------\n";
    }
    return 0;
}
