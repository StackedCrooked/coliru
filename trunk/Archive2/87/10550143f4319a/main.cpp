#include <string>
#include <map>
#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_hold.hpp>
#include <boost/spirit/include/qi_omit.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>
#include <boost/variant/recursive_variant.hpp>
#include <boost/foreach.hpp>
#include <exception>
#include <vector>
using namespace std;
using namespace boost;
using boost::spirit::qi::phrase_parse;
using boost::spirit::qi::char_;
using boost::spirit::qi::double_;
using boost::spirit::qi::eps;
using boost::spirit::qi::lit;
using boost::spirit::qi::_1;
using boost::spirit::qi::grammar;
using boost::spirit::qi::lexeme;
using boost::spirit::qi::symbols;
using boost::spirit::qi::rule;
using boost::spirit::qi::hold;
using boost::spirit::qi::omit;
using boost::spirit::_val;
using boost::spirit::ascii::space;
using boost::spirit::ascii::space_type;
using boost::phoenix::ref;
using boost::phoenix::push_back;
using boost::phoenix::at_c;

namespace sx {

    namespace parserInternal {

        /**
         * types of XNODE_
         */
        enum XTYPE_ {
            XTEXT_ ,
            XTAG_ ,
            S_ATTRIB_,
            R_ATTRIB_
        };

        /**
         * structure for boost spirit
         * parsetree datastructure
         */
        struct XNODE_ {

            /**
             * type of node
             */
            int type;

            /**
             * data of XText
             */
            string text;

            /**
             * data of XTag
             */
            string name;
            vector<XNODE_> nodes;

            /**
             * data of string attribute
             */
            string strID;
            string strAttrib;

            /**
             * data of real attribute
             */
            string rID;
            double rAttrib;

            /**
             * bug fix - stop parser from
             * taking characters it shouldn't
             * by assigning eat with the useless
             * string sequences
             */
            string eat;

        };

    }

}

BOOST_FUSION_ADAPT_STRUCT (
    sx::parserInternal::XNODE_ ,
    (int                                        ,type)      //  0
    (std::string                                ,text)      //  1 - XText
    (std::string                                ,name)      //  2 - XTag
    (std::vector<sx::parserInternal::XNODE_>   ,nodes)     //  3 - XTag
    (std::string                                ,strID)     //  4 - str. attrib
    (std::string                                ,strAttrib) //  5 - str. attrib
    (std::string                                ,rID)       //  6 - r. attrib
    (double                                     ,rAttrib)   //  7 - r. attrib
    (std::string                                ,eat)       //  8 - bug fix
)

namespace sx {

    namespace parserInternal {

        /**
         * filters comments out of the text
         */
        struct SXFilter: public grammar<string::iterator,string()> {

            /**
             * start rule
             */
            rule<string::iterator,string()> start;

            /**
             * recognizes a sequence starting with //, and anything
             * ending with newline
             */
            rule<string::iterator,string()> skipSmallComment;

            /**
             * recognizes a sequence starting with [slash][asterisk] and
             * anything ending with the two characters '*' and '/' in sequence
             */
            rule<string::iterator,string()> skipLargeComment;

            /**
             * recognizes newline
             */
            rule<string::iterator,string()> separator;

            /**
             * recognizes any text not containing the char sequences
             * [slash][asterisk] and //
             */
            rule<string::iterator,string()> acceptable;

            SXFilter(): SXFilter::base_type(start) {
                separator %= lexeme[(char_('\n') | char_("\r\n"))];
                acceptable %= *lexeme[char_ - lit("/*") - lit("//")];
                skipLargeComment %= lit("/*") >> *lexeme[char_ - lit("*/")] >> lit("*/");
                skipSmallComment %= lit ("//") >> *lexeme[char_ - separator];
                start %= eps >> acceptable >>
                    *(
                        (
                            omit[skipSmallComment]
                            | omit[skipLargeComment]
                        ) >> acceptable
                    )
                    ;
            }

        };

        /**
         * grammar for the parser
         */
        struct XGrammar: public grammar<string::iterator,XNODE_(),space_type> {

            /**
             * a tag
             */
            rule<string::iterator,XNODE_(),space_type> tag;

            /**
             * child nodes of a tag
             */
            rule<string::iterator,vector<XNODE_>(),space_type> nodelist;

            /**
             * identifyer - starts with a letter in a-zA-Z_:. , and can be
             * continued by a-zA-Z_0-9:. , must have at least one letter
             */
            rule<string::iterator,string()> identifyer;

            /**
             * any char sequence without the letter " of any length
             * bordered by the letter "
             */
            rule<string::iterator,string()> textdata;

            /**
             * attribute assigned with string value
             */
            rule<string::iterator,XNODE_(),space_type> strAttrib;

            /**
             * attribute assigned with double value
             */
            rule<string::iterator,XNODE_(),space_type> realAttrib;

            /**
             * simply textdata returning XNODE_
             */
            rule<string::iterator,XNODE_(),space_type> textNode;

            /**
             * constructor, makes tag to the node's root
             */
            XGrammar(): XGrammar::base_type(tag) {
                identifyer %= lexeme[char_("a-zA-Z_:.") >> *( char_("0-9a-zA-Z_:.") )];
                textdata %= lexeme['"' >> *(char_ - '"') >> '"'];
                strAttrib = 
                    identifyer[at_c<4>(_val) = _1] >> char_('=') >> 
                    textdata[at_c<5>(_val) = _1] >> char_(';')[at_c<0>(_val) = S_ATTRIB_];
                realAttrib =
                    identifyer[at_c<6>(_val) = _1] >> char_('=') >>
                    double_[at_c<7>(_val) = _1] >> char_(';')[at_c<0>(_val) = R_ATTRIB_];
                textNode = textdata[at_c<1>(_val) = _1][at_c<0>(_val) = XTEXT_];
                nodelist %= eps >>
                    *(
                        tag
                        | strAttrib
                        | realAttrib
                        | textNode
                    )
                    ;
                tag = eps >>
                    char_('(') >> identifyer[at_c<2>(_val) = _1] >> char_(')')[at_c<8>(_val) = _1] >>
                    (
                        char_('{') >>
                        nodelist[at_c<3>(_val) = _1] >>
                        char_('}')
                    | eps
                    )[at_c<0>(_val) = XTAG_]
                    ;
            }

        };

        void parseSXdata1(const string &data, string &output) {
            string filterable = data;
            string::iterator iter1 = filterable.begin();
            string::iterator iter2 = filterable.end();
            SXFilter filter;
            bool parsed = phrase_parse(
                iter1,
                iter2,
                filter,
                space,
                output
                );
            if(!parsed || iter1 != iter2) {
                throw std::exception();
            }
        }

        void parseSXdata2(string &data, parserInternal::XNODE_ &output) {
            string::iterator iter1 = data.begin();
            string::iterator iter2 = data.end();
            XGrammar grammar;
            bool parsed = phrase_parse(
                iter1,
                iter2,
                grammar,
                space,
                output
                );
            if(!parsed || iter1 != iter2) {
                throw std::exception();
            }
        }

    }
}

int main(int argc, char **argv) {
    string data = 
        "(testsx) {\n"
        "   (test) {\"hello world\"}\n"
        "   (test2) {\n"
        "       attrib1 = 123;\n"
        "       attrib2 = \"hey\";\n"
        "   }\n"
        "}"
        ;

    string iterable;
    sx::parserInternal::XNODE_ output; //root of parsetree
    sx::parserInternal::parseSXdata1(data,iterable);
    sx::parserInternal::parseSXdata2(iterable,output);

    return 0;
}
