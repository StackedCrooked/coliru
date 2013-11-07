    #include <string>
    #include <boost/spirit/include/qi.hpp>
    #include <boost/fusion/include/adapt_struct.hpp>
    
    using namespace boost::spirit::qi; 
    
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
    
    
        
    int main(int argc, char* argv[])
    {
        rule<std::wstring::const_iterator, identifier()> gr_identifier = eps >> raw[lexeme[(alpha | '_') >> *(alnum | '_')]];
        
        // Ok, compiles
        /*rule<std::wstring::const_iterator, problem()> gr_problem =       gr_identifier
                                                                      >> gr_identifier
                                                                      >> '('
                                                                      >>   gr_identifier
                                                                      >>   ')';*/
        // Fails
        rule<std::wstring::const_iterator, problem()> gr_problem =       gr_identifier
                                                                      >> gr_identifier
                                                                      >> '('
                                                                      >   gr_identifier
                                                                      >   ')';
        
        std::wstring input = L"foo goo(hoo)";
        /*bool dummy = phrase_parse(
                input.begin(), input.end(), 
                gr_problem,
                space);*/
    
        return EXIT_SUCCESS;
    }

    
    
    
    
    