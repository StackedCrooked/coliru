#include <iostream>
#include <string>
#include <locale>

#include <cstring>

int main()
{
     if( !strncasecmp("MyISAM" , "MYISAM" , 6) ) {
         std::cout << " First " << std::endl;
     }
     if(strncasecmp("MyISAM" , "MYISAM" , 6) != 0) {
         std::cout << " Second " << std::endl;
     }    
    
    return 0;
}