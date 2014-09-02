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
  int number;
  boost::fusion::vector1< int& > parameters(number);
  boost::function< void( int & ) > function = &Function;

  boost::fusion::invoke( function, parameters );
  
  std::cout << number << std::endl;

  return 0;
}
