    #include <iostream>
    #include <string>
    
    std::string::size_type my_find( std::string s, const char *cs )
    {
        std::string::size_type pos = s.find( cs ) ;
        std::cout << "position " << cs << " found in complete expression: "
            << pos << std::endl ;
        
        return pos ;
    }
    
    int main()
    {
       std::string s = "but I have heard it works even if you don't believe in it" ;
       std::string copy_s = s ;
       
       std::cout << "position of even before s.replace(0, 4, \"\" ): " 
             << s.find( "even" ) << std::endl ;
       std::cout << "position of  don't before s.replace(0, 4, \"\" ): " 
             << s.find( " don't" ) << std::endl << std::endl;
       
       copy_s.replace(0, 4, "" ) ;
       
       std::cout << "position of even after s.replace(0, 4, \"\" ): " 
             << copy_s.find( "even" ) << std::endl ;
       std::cout << "position of  don't after s.replace(0, 4, \"\" ): "
             << copy_s.find( " don't" ) << std::endl << std::endl;
      
       s.replace(0, 4, "" ).replace( my_find( s, "even" ) , 4, "only" )
            .replace( my_find( s, " don't" ), 6, "" );
       
       std::cout << "Result: " << s << std::endl ;
    }
