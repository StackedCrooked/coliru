#include <iostream>
#include <string>
#include <cctype>

int main()
{
    const std::string jabberwocky = "'Twas brillig, and the slithy toves\n"
                                    "Did gyre and gimble in the wabe;\n"
                                    "All mimsy were the borogoves,\n"
                                    "And the mome raths outgrabe.\n\n"

                                    "\"Beware the Jabberwock, my son\n"
                                    "The jaws that bite, the claws that catch!\n"
                                    "Beware the Jubjub bird, and shun\n"
                                    "The frumious Bandersnatch!\"\n" ;

   std::cout << jabberwocky << "\n-----------------------\n\n" ;

   for( char c : jabberwocky ) // http://www.stroustrup.com/C++11FAQ.html#for
       if( !std::ispunct(c) ) std::cout << c ;
}
