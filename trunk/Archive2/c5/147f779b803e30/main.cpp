    #include <string>
    #include <boost/spirit/include/qi.hpp>
    #include <boost/fusion/include/adapt_struct.hpp>
    
    namespace qi=boost::spirit::qi; 
    
    struct identifier
	{
		std::wstring name;
	};
    
    struct problem
    {
        identifier _1;
        identifier _2;
        identifier _3;
    };
    
    BOOST_FUSION_ADAPT_STRUCT(
        identifier,
    	(std::wstring, name)
    )
    
    BOOST_FUSION_ADAPT_STRUCT(
        problem,
        (identifier, _1)
        (identifier, _2)
        (identifier, _3)
    )
    
    
    template <typename Expr, typename Iterator = boost::spirit::unused_type>
    struct attribute_of_qi_component
    {
        typedef typename boost::spirit::result_of::compile<
            qi::domain, Expr
        >::type parser_expression_type;

        typedef typename boost::spirit::traits::attribute_of<
            parser_expression_type, 
            boost::spirit::unused_type, Iterator
        >::type type;
    };
    
    template <typename Expr>
    void print_attribute(const Expr&)
    {
        std::cout << typeid(typename attribute_of_qi_component<Expr>::type).name() << std::endl;
    }
    
    
        
    int main(int argc, char* argv[])
    {
        qi::rule<std::wstring::const_iterator, identifier()> gr_identifier = qi::eps >> qi::raw[qi::lexeme[(qi::alpha | '_') >> *(qi::alnum | '_')]];
        
        // Ok, compiles
        /*rule<std::wstring::const_iterator, problem()> gr_problem =       gr_identifier
                                                                      >> gr_identifier
                                                                      >> '('
                                                                      >>   gr_identifier
                                                                      >>   ')';*/
        // Fails
        /*rule<std::wstring::const_iterator, problem()> gr_problem =       gr_identifier
                                                                      >> gr_identifier
                                                                      >> '('
                                                                      >   gr_identifier
                                                                      >   ')';*/
                                                                      
        std::cout << "Attribute of the rule with only '>>':" << std::endl;
        print_attribute(gr_identifier >> gr_identifier >> '(' >> gr_identifier >> ')');
        
        std::cout << "Attribute of the rule mixing '>>' and '>' :" << std::endl;
        print_attribute(gr_identifier >> gr_identifier >> '(' > gr_identifier > ')');
        
        std::wstring input = L"foo goo(hoo)";
        /*bool dummy = phrase_parse(
                input.begin(), input.end(), 
                gr_problem,
                space);*/
    
        return EXIT_SUCCESS;
    }

    
    
    
    
    