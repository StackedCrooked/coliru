//#define BOOST_SPIRIT_DEBUG
#include <iostream>
#include <sstream>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>
#include <boost/spirit/include/classic_position_iterator.hpp>
#include <boost/fusion/adapted/struct/adapt_struct.hpp>

namespace qi = boost::spirit::qi;

struct message_data //awful name, use something more appropriate
{
    message_data():seqNo(1){}
    
    std::string sender;
    std::string receiver;
    unsigned int seqNo;
};

struct message
{
  std::string title;
  message_data main; //awful names again
  message_data ref;
  std::string id;
};

BOOST_FUSION_ADAPT_STRUCT(
    message_data,
    (std::string, sender)
    (std::string, receiver)
    (unsigned int, seqNo)
)

BOOST_FUSION_ADAPT_STRUCT(
    message,
    (std::string, title)
    (message_data, main)
    (message_data, ref)
    (std::string, id)
)

template<typename Iterator>
struct MyQiGrammar : qi::grammar<Iterator, message(), qi::space_type>
{
  MyQiGrammar() : MyQiGrammar::base_type(start) {
    qi::uint_parser<unsigned int, 10, 3, 3> uint_3p;

    delim     = qi::char_("-/");            // some values are delimited by '-' or '/'

    title    %= qi::repeat(3)[qi::upper];   // exactly 3 upper case letters
    sender   %= +qi::upper;                 // at least one upper case letter
    receiver %= +qi::upper;                 // at least one upper case letter
    seqNo    %= uint_3p;                    // exactly 3 digits (e.g. 001)
    id       %= qi::repeat(1,7)[qi::alnum]; // at least 1 upper case letter and maximum 7
    
    data     %= sender >> delim >> receiver >> seqNo;

    start    %=
        '('
        >> title
        >> data
        >> -(data)
        >> delim >> id
        >>
        ')';
        
    BOOST_SPIRIT_DEBUG_NODES( (start)(id)(seqNo)(receiver)(sender)(title)(data)(delim) )
  }

  qi::rule<Iterator> delim;
  qi::rule<Iterator, std::string(), qi::space_type> title;
  qi::rule<Iterator, std::string(), qi::space_type> sender, receiver, id;
  qi::rule<Iterator, unsigned int(), qi::space_type> seqNo;
  qi::rule<Iterator, message_data(), qi::space_type> data;
  qi::rule<Iterator, message(), qi::space_type> start;
};

int
main(int args, char** argv)
{
  typedef std::istreambuf_iterator<char> base_iterator_type;
  typedef boost::spirit::multi_pass<base_iterator_type> forward_iterator_type;
  typedef boost::spirit::classic::position_iterator2<forward_iterator_type> pos_iterator_type;
  typedef MyQiGrammar<pos_iterator_type> qi_parser;

  std::string rawMsg = "(ABCZ/Y002-GWI4576&)";
  qi_parser myGrammarParser;
  message msg;

  std::istringstream iss(rawMsg);
  base_iterator_type in_begin(iss);
  forward_iterator_type fwd_begin = boost::spirit::make_default_multi_pass(in_begin);
  forward_iterator_type fwd_end;
  pos_iterator_type pos_begin(fwd_begin, fwd_end);
  pos_iterator_type pos_end;

  std::cout << rawMsg << std::endl;

  try {
    bool msgRes = qi::phrase_parse(pos_begin, pos_end,
                                   myGrammarParser,
                                   qi::space,
                                   msg);

    if(msgRes) {
      std::cout << "Parsing succeeded!" << std::endl;

      if(pos_begin == pos_end) {
        std::cout << "Full match!" << std::endl;
        std::cout << "Title                  : " << msg.title << std::endl;
        std::cout << "Sender                 : " << msg.main.sender << std::endl;
        std::cout << "Receiver               : " << msg.main.receiver << std::endl;
        std::cout << "Sequence number        : " << msg.main.seqNo << std::endl;
        std::cout << "Sender (ref.)          : " << msg.ref.sender << std::endl;
        std::cout << "Receiver (ref.)        : " << msg.ref.receiver << std::endl;
        std::cout << "Sequence number (ref.) : " << msg.ref.seqNo << std::endl;
        std::cout << "Message Identifier     : " << msg.id << std::endl;
      }
    } else {
      std::cout << "Parsing failed!" << std::endl;
      std::cout << "Stopped at: " << pos_begin.get_position().line
                << ":" << pos_begin.get_position().column << std::endl;
    }
  } catch(qi::expectation_failure<pos_iterator_type>& e) {
    const boost::spirit::classic::file_position_base<std::string>& pos = e.first.get_position();
    std::stringstream ss;

    ss << "Parse error at line " << pos.line << " column " << pos.column
       << "\n\t" << e.first.get_currentline()
       << "\n\t" << std::string(pos.column, ' ') << "^--here";

    std::cerr << ss.str() << std::endl;
  }

  return 0;
}