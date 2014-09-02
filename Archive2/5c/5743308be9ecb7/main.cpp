#include <iostream>
#include <boost/bind.hpp>
#include <boost/function.hpp>

#include <boost/fusion/functional.hpp>

void Function( int input) //REMOVED THE REF
{
  std::cout << input << std::endl;
}

int main( int, char ** )
{
  boost::fusion::vector1< int > parameters(3); //INITIALIZED THE ELEMENT TO 3, IT WOULD BE 0 BY DEFAULT
  boost::function< void( int ) > function = &Function; //REMOVED THE REF

  boost::fusion::invoke( function, parameters );

  return 0;
}

