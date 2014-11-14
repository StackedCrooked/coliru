#include <iostream>
#include <string>

std::string::size_type my_find( size_t id, std::string s, const char *cs )
{
    std::string::size_type pos = s.find( cs ) ;
    std::cout << "find: " << id << " pos: " << pos << std::endl ;
    
    return pos ;
}

int main()
{
   std::string s = "but I have heard it works even if you don't believe in it" ;
   std::string copy_s = s ;
   std::cout << "pos even: " << s.find( "even" ) << std::endl ;
   std::cout << "pos don't: " << s.find( " don't" ) << std::endl ;
   copy_s.replace(0, 4, "" ) ;
   std::cout << "pos even: " << copy_s.find( "even" ) << std::endl ;
   std::cout << "pos don't: " << copy_s.find( " don't" ) << std::endl ;
   //s.replace(0, 4, "" ).replace(s.find( "even" ), 4, "only" ).replace(s.find( " don't" ), 6, "" );
   s.replace(0, 4, "" ).replace( my_find( 1, s, "even" ) , 4, "only" ).replace( my_find( 2, s, " don't" ), 6, "" );
   
   
   std::cout << s << std::endl ;
}
