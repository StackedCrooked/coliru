#include <string>
#include <iostream>
#include <boost/foreach.hpp>

int main()
{
    std::string hello( "Hello, world!" );

    BOOST_FOREACH( char ch, hello )
    {
        std::cout << ch;
    }
    
    
    int array[] = { 1,6,2,7,9,3,8};
    std::size_t numelements = sizeof(array)/sizeof(int);
    
    std::cout << std::endl << "Num Elements=" << numelements << std::endl;
    
   if( numelements > 0)
   {
       int currentmax = array[0];
       
       BOOST_FOREACH(int i,array)
       {
           std::cout << "i =" << i << std::endl;
           if ( currentmax < i)
           {
               currentmax = i;
           }
       }
       
       std::cout << "Max =" << currentmax << std::endl; 
   }

    return 0;
}

