// Public Domain Dedication 
// CC0 1.0 Universal
// http://creativecommons.org/publicdomain/zero/1.0/
//
// Written by olibre <olibre@Lmap.org> to answer:
// http://stackoverflow.com/questions/13830158


// Traits class to check if a type is iterable

template<typename C>
struct is_iterable
{
  typedef long false_type; 
  typedef char true_type; 
    
  template<class T> static false_type check(...); 
  template<class T> static true_type  check(int, 
                    typename T::const_iterator = C().end()); 
    
  enum { value = sizeof(check<C>(0)) == sizeof(true_type) }; 
};


// Test code

#include <iostream>
#include <set>

int main()
{
    std::cout <<"set="<< is_iterable< std::set<int> >::value <<'\n';
    std::cout <<"int="<< is_iterable< int           >::value <<'\n';
}
