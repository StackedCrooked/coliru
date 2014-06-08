#include <iostream>
#include <iterator>
#include <algorithm>
#include <fstream>



int main ()
{

std::ifstream myfile("test.txt") ;
char mychar ='i';

    std::size_t result = std::count( std::istream_iterator<char>(myfile), 
                                     std::istream_iterator<char>(),
                                      mychar 
                                    ) ;

std::cout << "Result :" << result << std::endl ;

myfile.close( );

}

