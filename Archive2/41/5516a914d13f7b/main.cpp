#define BOOST_SPIRIT_USE_PHOENIX_V3
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
        namespace Nodes
        {
            struct Text {
                std::string text;

                // single element structs don't work well with Fusion Adapation...
                Text(std::string text = "") : text(std::move(text)) {}
            };

            template <typename V> struct Attr_ {
                std::string ID;
                V           Attrib;

                Attr_(std::string ID = "", V Attrib = V())
                    : ID(std::move(ID)), Attrib(std::move(Attrib))
                { }
            };

            typedef Attr_<std::string> SAttr;
            typedef Attr_<double>      RAttr;

            struct Tag;

        }

        typedef boost::variant<
            Nodes::Text,
            boost::recursive_wrapper<Nodes::Tag>,
            Nodes::SAttr,
            Nodes::RAttr
        > Node;

        namespace Nodes
        {
            // recursive node
            struct Tag {
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
            XTYPE_ operator()(Nodes::Text  const&) const { return XTEXT_;    }
            XTYPE_ operator()(Nodes::Tag   const&) const { return XTAG_;     }
            XTYPE_ operator()(Nodes::SAttr const&) const { return S_ATTRIB_; }
            XTYPE_ operator()(Nodes::RAttr const&) const { return R_ATTRIB_; }
        };
    }
}

BOOST_FUSION_ADAPT_STRUCT(sx::parserInternal::Nodes::Tag, (std::string, name) (std::vector<sx::parserInternal::Node>, nodes))
BOOST_FUSION_ADAPT_STRUCT(sx::parserInternal::Nodes::Text, (std::string, text))
BOOST_FUSION_ADAPT_TPL_STRUCT((V), (sx::parserInternal::Nodes::Attr_)(V), (std::string, ID)(V, Attrib))

namespace sx {
    namespace parserInternal {

        /**
         * grammar for the parser
         */
        template <
            typename It = std::string::const_iterator,
            typename Skipper = qi::rule<It>
        >
        struct XGrammar: qi::grammar<It,Node(),Skipper> {

            qi::rule<It, std::vector<Node>(), Skipper> nodelist;
            qi::rule<It, Node(),              Skipper> node, start;
            qi::rule<It, Nodes::Tag(),        Skipper> tag;
            qi::rule<It, Nodes::Text(),       Skipper> textNode;
            qi::rule<It, Nodes::SAttr(),      Skipper> strAttrib;
            qi::rule<It, Nodes::RAttr(),      Skipper> realAttrib;
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

        parserInternal::Node parseSXdata2(std::string const& data) {
            typedef std::string::const_iterator It;
            typedef qi::rule<It> Skipper;

            It iter1 = data.begin();
            It iter2 = data.end();

            static const Skipper skipper = qi::space
                                         | ("/*" > *(qi::char_ - "*/") > "*/")
                                         | ("//" > *(qi::char_ - qi::eol))
                                         ;
            static const XGrammar<It, Skipper> grammar;

            parserInternal::Node output;

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
        "}"
        ;

    sx::parserInternal::Node output; //root of parsetree
    output = sx::parserInternal::parseSXdata2(data);
}
