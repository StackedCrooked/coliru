#define BOOST_SPIRIT_DEBUG
#include <boost/config/warning_disable.hpp>
#include <boost/fusion/adapted/struct.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/include/io.hpp>
#include <boost/variant/recursive_variant.hpp>
#include <stdexcept>
#include <vector>
#include <string>
#include <map>

namespace qi  = boost::spirit::qi;
namespace phx = boost::phoenix;

namespace sx {

    namespace parserInternal {

        /**
         * structure for boost spirit
         * parsetree datastructure
         */
        namespace AST
        {
            struct TextNode {
                std::string text;

                // single element structs don't work well with Fusion Adapation...
                TextNode(std::string text = "") : text(std::move(text)) {}
            };

            template <typename V> struct Attr_ {
                std::string ID;
                V           Attrib;

                Attr_(std::string ID = "", V Attrib = V())
                    : ID(std::move(ID)), Attrib(std::move(Attrib))
                { }
            };

            typedef Attr_<std::string> StringAttribute;
            typedef Attr_<double>      RealAttribute;

            struct TagNode;

            typedef boost::variant<
                TextNode,
                boost::recursive_wrapper<TagNode>,
                StringAttribute,
                RealAttribute
            > Node;

            // recursive node
            struct TagNode {
                std::string       name;
                std::vector<Node> nodes;
            };
        }

        /**
         * types of Node; example of how you can easily visit nodes
         */
        enum XTYPE_ { XTEXT_ , XTAG_ , S_ATTRIB_, R_ATTRIB_ };
        struct Identify : boost::static_visitor<XTYPE_>
        {
            XTYPE_ operator()(AST::TextNode        const&) const { return XTEXT_;    }
            XTYPE_ operator()(AST::TagNode         const&) const { return XTAG_;     }
            XTYPE_ operator()(AST::StringAttribute const&) const { return S_ATTRIB_; }
            XTYPE_ operator()(AST::RealAttribute   const&) const { return R_ATTRIB_; }
        };
    }
}

BOOST_FUSION_ADAPT_STRUCT(sx::parserInternal::AST::TagNode, (std::string, name) (std::vector<sx::parserInternal::AST::Node>, nodes))
BOOST_FUSION_ADAPT_STRUCT(sx::parserInternal::AST::TextNode, (std::string, text))
BOOST_FUSION_ADAPT_TPL_STRUCT((V), (sx::parserInternal::AST::Attr_)(V), (std::string, ID)(V, Attrib))

namespace sx {
    namespace parserInternal {

        /**
         * grammar for the parser
         */
        template <
            typename It = std::string::const_iterator,
            typename Skipper = qi::rule<It>
        >
        struct XGrammar: qi::grammar<It, AST::Node(), Skipper> {

            qi::rule<It, std::vector<AST::Node>(), Skipper> nodelist;
            qi::rule<It, AST::Node(),              Skipper> node, start;
            qi::rule<It, AST::TagNode(),           Skipper> tag;
            qi::rule<It, AST::TextNode(),          Skipper> textNode;
            qi::rule<It, AST::StringAttribute(),   Skipper> strAttrib;
            qi::rule<It, AST::RealAttribute(),     Skipper> realAttrib;

            // natural lexemes (using `lexeme` there is a bit redundant):
            qi::rule<It, std::string()> identifier;
            qi::rule<It, std::string()> quoted_text;

            /**
             * constructor, makes tag to the node's root
             */
            XGrammar(): XGrammar::base_type(start) {

                using namespace qi;

                identifier  = lexeme[ char_("a-zA-Z_:.") >> *char_("0-9a-zA-Z_:.") ];
                quoted_text = lexeme[ '"' >> *(char_ - '"') >> '"' ];

                strAttrib   = identifier >> '=' >> quoted_text >> ';';
                realAttrib  = identifier >> '=' >> double_     >> ';';
                textNode    = quoted_text;

                nodelist    = '{' >> *node >> '}';

                node        = tag
                            | strAttrib
                            | realAttrib
                            | textNode
                            ;

                tag         = '(' >> identifier >> ')' >> -nodelist;
                            ;

                // allow only tags at root of parse tree
                start       = tag;

                BOOST_SPIRIT_DEBUG_NODES((start)(tag)(node)(nodelist)(textNode)(realAttrib)(strAttrib)(quoted_text)(identifier))
            }
        };

        parserInternal::AST::Node parseSXdata2(std::string const& data) {
            typedef std::string::const_iterator It;
            typedef qi::rule<It> Skipper;

            It iter1 = data.begin();
            It iter2 = data.end();

            static const Skipper skipper = qi::space
                                         | ("/*" > *(qi::char_ - "*/") > "*/")
                                         | ("//" > *(qi::char_ - qi::eol))
                                         ;
            static const XGrammar<It, Skipper> grammar;

            parserInternal::AST::Node output;
            bool parsed = qi::phrase_parse(iter1, iter2, grammar, skipper, output);

            if(!parsed || iter1 != iter2) {
                throw std::runtime_error("Parsing failed");
            }

            return output;
        }

    }
}

int main() {
    std::string const data =
        "(testsx) {\n"
        "   (test) {\"hello world\"}\n"
        "   (test2) {\n"
        "       attrib1 = 123;\n"
        "       attrib2 = \"hey\";\n"
        "   }\n"
        "}";

    sx::parserInternal::AST::Node output; //root of parsetree
    output = sx::parserInternal::parseSXdata2(data);
}
