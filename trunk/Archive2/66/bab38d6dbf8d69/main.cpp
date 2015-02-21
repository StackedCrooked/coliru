#include <iostream>
#include <boost/container/vector.hpp>


template <class Container, class ConstIterator>
typename Container::iterator 
noconst(Container& c, ConstIterator it)
{ return c.erase(it, it); }


int main() {
   boost::container::vector<int> dummy(1, 1);   
   boost::container::vector<int>::const_iterator const constIt(dummy.begin());
   boost::container::vector<int>::iterator const it = noconst(dummy, constIt);
   std::cout << *it << std::endl;
}
