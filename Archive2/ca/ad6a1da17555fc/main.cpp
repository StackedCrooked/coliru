    #define BOOST_SPIRIT_USE_PHOENIX_V3
    #include <boost/config/warning_disable.hpp>
    #include <boost/spirit/include/qi.hpp> 
    #include <boost/spirit/repository/include/qi_subrule.hpp>  
    #include <boost/spirit/include/qi_symbols.hpp>
    #include <boost/spirit/include/phoenix.hpp>
    #include <string> 
    #include <iostream> 

    using std::cout; 
    using std::endl; 
    using std::cerr; 

    struct Dog 
    {
       std::string Name; 
       bool Barks;
       bool HasATail; 
       std::string Address; 
    }; 

    struct Bird
    {
        std::string Name; 
        bool Tweets; 
        std::string Address; 
    };

    namespace qi = boost::spirit::qi;
	namespace repo = boost::spirit::repository;
	namespace ascii = boost::spirit::ascii;
	namespace phx = boost::phoenix; 

    template <typename Iterator>
    struct ZooGrammar : public qi::grammar<Iterator, ascii::space_type>
    {
         ZooGrammar() : ZooGrammar::base_type(start_)
         {
           
            using qi::char_; 
			using qi::lit_; 
			using qi::_1;
			using boost::phoenix::ref; 

            boost::spirit::qi::symbols<char, bool> yesno_; 
            yesno_.add("Y", true)("N", false); 

             start_ = (
                 dog_ | bird_, 
                 dog_ = "DOG" >> lit_[ref(d.Name) = _1]>> '|'
                         >>"Barks=">>yesno_[ref(d.Barks) = _1] >>'|'
                         >>"Has a Tail=">>yesno_[ref(d.HasATail) = _1] >> '|'
                         >>lit_[ref(d.Address) = _1]
                 , 
                 bird_ = "BIRD" >> lit_[ref(b.Name) = _1]>> '|'
                         >>"Tweets=">>yesno_[ref(b.Tweets) = _1] >>'|'
                         >>lit_[ref(b.Address) = _1]
             );
         } 

        qi::rule<Iterator, ascii::space_type> start_; 
		repo::qi::subrule<0> dog_;
		repo::qi::subrule<1> bird_; 
        Bird b;
        Dog d; 
    }; 
    
    
    int main()
    {
        std::string test1="DOG | Name=tim | Barks=Yes | Has a Tail=N | Address=3 infinite loop"; 
        std::string test2="BIRD| Name=poc | Tweets=Yes| Address=10 stack overflow street"; 
        using boost::spirit::ascii::space;
        typedef std::string::const_iterator iterator_type;
        typedef ZooGrammar<iterator_type> grammar;
	    iterator_type start = test1.begin(); 
	    iterator_type end   = test1.end();
	    ZooGrammar g; 
	    if(boost::spirit::qi::phrase_parse(start, end, g, space))
	    {
		    cout<<"matched"<<endl; 
	    }
    }