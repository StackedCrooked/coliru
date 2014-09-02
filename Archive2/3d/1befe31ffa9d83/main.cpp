#include <iostream>
#include <boost/bind.hpp>
#include <boost/function.hpp>

#include <boost/fusion/functional.hpp>

void Function( int & output )
{
  output = 12;
}

int main( int, char ** )
{
  int number; //ADDED A VARIABLE
  boost::fusion::vector1< int& > parameters(number); //CHANGED THE ELEMENT TYPE TO A REF, AND INITIALIZED IT WITH THE VARIABLE
  boost::function< void( int & ) > function = &Function;

  boost::fusion::invoke( function, parameters );
  
  std::cout << number << std::endl;

  return 0;
}
