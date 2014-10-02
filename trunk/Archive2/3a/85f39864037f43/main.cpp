#include <list>         // std::list
#include <iostream>     // std::cout
#include <iterator>     // std::distance

int main ()
{
  std::list<int> mylist;
  for (int i = 0; i < 10; i++) {
      mylist.push_back (i * 10);
  }

  std::list<int>::iterator first = mylist.begin();

  std::list<int> sec_list;
  std::list<int>::iterator last = sec_list.begin();

  std::cout << "The distance is: " << std::distance(first,last) << '\n';

  return 0;
}
