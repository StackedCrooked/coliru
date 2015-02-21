#include <iostream>
#include <vector>


template <class Container, class ConstIterator>
typename Container::iterator 
noconst(Container& c, ConstIterator it)
{ return c.erase(it, it); }


int main() {
   std::vector<int> dummy {1};   
   std::vector<int>::const_iterator const constIt(dummy.begin());
   std::vector<int>::iterator const it = noconst(dummy, constIt);
   std::cout << *it << std::endl;
}
