//#define BOOST_SPIRIT_DEBUG

#include <boost/spirit/include/qi_core.hpp>
#include <boost/container/vector.hpp>
#include <boost/fusion/include/adapt_struct_named.hpp>
#include <vector>

namespace parser
{
    struct ptree
    {
        ptree():children(),name(),length(){}
        boost::container::vector<ptree> children;
        std::string name;
        int length;
    };
    
    void print(const ptree& tree, int indent=0)
    {
        for(int i=0;i<indent;++i)
            std::cout << ' ';
        for(int i=0;i<tree.length;++i)
            std::cout << '-';
        std::cout << tree.name << std::endl;
        for(int i=0;i<tree.children.size();++i)
            print(tree.children[i],indent+tree.length);
    }
}

BOOST_FUSION_ADAPT_STRUCT(
    parser::ptree,
    (boost::container::vector<parser::ptree>, children)
    (std::string, name)
    (int, length)
)

BOOST_FUSION_ADAPT_STRUCT_NAMED(
    parser::ptree,
    leaf,
    (std::string, name)
    (int, length)
)

namespace parser
{
    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;
    
    using boost::fusion::adapted::leaf;

    template<typename Iterator>
    struct newick_grammar : qi::grammar<Iterator, ptree(), ascii::space_type>
    {
        public:
            newick_grammar() : newick_grammar::base_type(tree)
            {
                using qi::int_;
                using ascii::char_;
                using qi::lit;

                /* This is the only grammar that works fine:
                 * http://evolution.genetics.washington.edu/phylip/newick_doc.html */
                 
                tree = descendant_list >> -label >> -branch_length >> ';';
                descendant_list = '(' >> subtree % ',' >> ')';
                subtree = branch | leaf;
                branch = descendant_list >> -label >> -branch_length;
                leaf = label >> -branch_length;
                label = +(char_ - (lit(':') | ')' | ',' | ';') );
                branch_length = ":0." >> int_;


                BOOST_SPIRIT_DEBUG_NODE(label);
                BOOST_SPIRIT_DEBUG_NODE(branch_length);
                BOOST_SPIRIT_DEBUG_NODE(subtree);
                BOOST_SPIRIT_DEBUG_NODE(descendant_list);
                BOOST_SPIRIT_DEBUG_NODE(tree);
            }

        private:

            /* grammar rules */
            qi::rule<Iterator, parser::ptree(), ascii::space_type> tree, subtree;
            qi::rule<Iterator, boost::container::vector<ptree>(), ascii::space_type> descendant_list;
            qi::rule<Iterator, parser::ptree(), ascii::space_type> branch;
            qi::rule<Iterator, parser::leaf(), ascii::space_type> leaf;
            qi::rule<Iterator, int(), ascii::space_type> branch_length;
            qi::rule<Iterator, std::string()> label;
    };
}

int main()
{
    std::string test="(((One:0.1,Two:0.2)Sub1:0.3,(Three:0.4,Four:0.5)Sub2:0.6)Sub3:0.7,Five:0.8)Root:0.9;";
    std::string::const_iterator iter=test.begin(), end=test.end();
    
    parser::newick_grammar<std::string::const_iterator> parser;
    
    parser::ptree parsed_tree;
    
    bool result=parser::qi::phrase_parse(iter,end,parser,parser::ascii::space,parsed_tree);
    if(result && iter==end)
    {
        std::cout << "Success." << std::endl;
        print(parsed_tree);
    }
    else
    {
        std::cout << "Failure. Unparsed: " << std::string(iter,end) << std::endl;
    }
}