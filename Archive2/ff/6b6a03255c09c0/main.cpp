#include <boost/lexical_cast.hpp>
#include <iostream>

int main( int argc, char * argv[] )
{
    int int1       = 0;
    double double1 = 0;
    float float1   = 0;
    
    std::string str = "words" 
               + boost::lexical_cast<std::string>(int1) 
               + boost::lexical_cast<std::string>(double1) 
               + boost::lexical_cast<std::string>(float1)
    ;
    
    std::cout << str;
}
