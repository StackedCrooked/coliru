#define BOOST_SPIRIT_USE_PHOENIX_V3
//#define BOOST_SPIRIT_DEBUG
#include <boost/spirit/include/qi_core.hpp>
#include <boost/spirit/include/qi_attr.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_bind.hpp>
#include <boost/spirit/include/lex_lexertl.hpp>
#include <boost/spirit/include/lex_lexertl_position_token.hpp>
#include <boost/none.hpp>
#include <boost/cstdint.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <string>
#include <exception>
#include <vector>

namespace lex = boost::spirit::lex;
namespace px = boost::phoenix;
namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

// std::string test = " EVENT 1:sihan { OPTIONAL 123:hassan int4; OPTIONAL 123:hassan int4; } ";


template <typename Lexer>
struct tokens : lex::lexer<Lexer>
{
    tokens()
        : left_curly("\"{\""),
        right_curly("\"}\""),
        left_paren("\"(\""),
        right_paren("\")\""),
        colon(":"),
        scolon(";"),
        namespace_("(?i:namespace)"),
        event("(?i:event)"),
        optional("(?i:optional)"),
        required("(?i:required)"),
        repeated("(?i:repeated)"),
        t_int_4("(?i:int4)"),
        t_int_8("(?i:int8)"),
        t_string("(?i:string)"),
        ordinal("\\d+"),
        identifier("\\w+")

    {
        using boost::spirit::lex::_val;

        this->self
            = 
              left_curly    //[ std::cout << px::val("lpar") << std::endl]
            | right_curly   //[ std::cout << px::val("rpar") << std::endl]
            | left_paren
            | right_paren
            | colon               //[ std::cout << px::val("colon") << std::endl]
            | scolon
            | namespace_         // [ std::cout << px::val("kw namesapce") << std::endl]
            | event              // [ std::cout << px::val("kw event") << std::endl]
            | optional            //[ std::cout << px::val("optional ")  << "-->" << _val << "<--" << std::endl]
            | required            //[ std::cout << px::val("required") << std::endl]
            | repeated
            | t_int_4
            | t_int_8
            | t_string
            | ordinal             //[ std::cout << px::val("val ordinal (") << _val << ")" << std::endl]
            | identifier          //[std::cout << px::val("val identifier(") << _val << ")" << std::endl]
    		

            | lex::token_def<>("[ \\t\\n]+")   [lex::_pass = lex::pass_flags::pass_ignore]
			;
    }


    lex::token_def<lex::omit> left_curly, right_curly, colon, scolon,repeated, left_paren, right_paren;
    lex::token_def<lex::omit> namespace_, event, optional, required,t_int_4, t_int_8, t_string;
    lex::token_def<boost::uint32_t> ordinal;
    lex::token_def<> identifier;
};

enum event_entry_qualifier
{
    ENTRY_OPTIONAL,
    ENTRY_REQUIRED,
    ENTRY_REPEATED
};

enum entry_type
{
    RBL_INT4,
    RBL_INT8,
    RBL_STRING,
    RBL_EVENT
};

struct oid
{
    boost::uint32_t   ordinal;
    std::string       name;
};

BOOST_FUSION_ADAPT_STRUCT
(
  oid,
  (boost::uint32_t, ordinal)
  (std::string, name)
)

std::ostream& operator<<(std::ostream& os, const oid& val)
{
	return os << val.ordinal << "-" << val.name;
}

struct type_descriptor
{
    entry_type  type_id;
    std::string referenced_event;
};

BOOST_FUSION_ADAPT_STRUCT
(
  type_descriptor,
  (entry_type, type_id)
  (std::string, referenced_event)
)

std::ostream& operator<<(std::ostream& os, const type_descriptor& val)
{
	return os << val.type_id << "-" << val.referenced_event;
}

struct event_entry
{
    event_entry_qualifier  qualifier;
    oid                   identifier;
    type_descriptor       descriptor;
};


BOOST_FUSION_ADAPT_STRUCT
(
  event_entry,
  (event_entry_qualifier, qualifier)
  (oid, identifier)
  (type_descriptor, descriptor)
)

std::ostream& operator<<(std::ostream& os, const event_entry& val)
{
	return os << val.qualifier << "-" << val.identifier << "-" << val.descriptor;
}

struct event_descriptor
{
    oid                       identifier;
    std::vector<event_entry>  event_entries;
};



BOOST_FUSION_ADAPT_STRUCT
(
    event_descriptor,
    (oid, identifier)
    (std::vector<event_entry>, event_entries)
)

std::ostream& operator<<(std::ostream& os, const event_descriptor& val)
{
	os << val.identifier << "[";
	for(const auto& entry: val.event_entries)
		os << entry;
	os << "]";
	return os;
}

struct build_string_impl
{
	template <typename Sig>
	struct result;
	template <typename This, typename Iter1, typename Iter2>
	struct result<This(Iter1,Iter2)>
	{
		typedef std::string type;
	};
	
	template <typename Iter1, typename Iter2>
    std::string	operator()(Iter1 begin, Iter2 end) const
	{
		return std::string(begin->begin(),end->begin());
	}
};

px::function<build_string_impl> build_string;

template <typename Iterator, typename Lexer>
struct grammar : qi::grammar<Iterator,event_descriptor() >
{
    template <typename TokenDef>
    grammar(TokenDef const& tok)
      : grammar::base_type(event_descriptor_)
    {
      using qi::_val;
      //start = event;
      event_descriptor_ = tok.event >> oid_ >> tok.left_curly >> *(event_entry_) >> tok.right_curly;

      event_entry_ = event_qualifier >> oid_ >> type_descriptor_ >> tok.scolon;

      event_qualifier = tok.optional [ _val = ENTRY_OPTIONAL]  
                      | tok.required [ _val = ENTRY_REQUIRED]
                      | tok.repeated [ _val = ENTRY_REPEATED];

      oid_  = tok.ordinal 
            >> tok.colon 
            >> tok.identifier;

      type_descriptor_ 
          = (( atomic_type >> qi::attr("")) 
          | ( event_type >> tok.left_paren >> tok.identifier >> tok.right_paren));

      atomic_type = tok.t_int_4         [ _val = RBL_INT4]
              | tok.t_int_8             [ _val = RBL_INT8]
              | tok.t_string            [ _val = RBL_STRING];

      event_type = tok.event            [_val = RBL_EVENT];

      using namespace qi::labels;
      qi::on_success(event_entry_,std::cout << _val << " " << build_string(_1,_3) << std::endl);
	 // BOOST_SPIRIT_DEBUG_NODES( (event_descriptor_)(event_entry_)(event_qualifier)(oid_)(type_descriptor_)(atomic_type)(event_type) );
	  
    }

    qi::rule<Iterator> start;
    qi::rule<Iterator, event_descriptor()> event_descriptor_; 
    qi::rule<Iterator, event_entry()> event_entry_;
    qi::rule<Iterator, event_entry_qualifier()> event_qualifier;
    qi::rule<Iterator, entry_type()> atomic_type;
    qi::rule<Iterator, entry_type()> event_type;
    qi::rule<Iterator, type_descriptor()> type_descriptor_;
    qi::rule<Iterator, oid()> oid_;


};

std::string test = " EVENT 1:sihan { OPTIONAL 123:hassan int4; OPTIONAL 321:hassan2 int4; } ";

int main()
{
    typedef lex::lexertl::position_token<std::string::iterator, boost::mpl::vector<boost::uint32_t, std::string> > token_type;
    typedef lex::lexertl::actor_lexer<token_type> lexer_type;
    typedef tokens<lexer_type>::iterator_type iterator_type;

    tokens<lexer_type> token_lexer;
    grammar<iterator_type,tokens<lexer_type>::lexer_def> grammar(token_lexer);

    std::string::iterator it = test.begin();
    iterator_type first = token_lexer.begin(it, test.end());
    iterator_type last = token_lexer.end();

    bool r; 

    r = qi::parse(first, last, grammar);

    if(r)
        ;
    else
    {
        std::cout << "parsing failed" << std::endl;
    }
}