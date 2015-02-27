// transform algorithm example
#include <iostream>     // std::cout
#include <algorithm>    // std::transform
#include <vector>       // std::vector
#include <boost/bind.hpp>


struct A
{
    explicit A(int d): m_d(d) {};
    A(): m_d(0) {};
    int GetValue() {return m_d; };
private:
    int m_d;
};

A some_function (int i) { return A(2*i); }

int main () {
  std::vector<int> foo;
  std::vector<A> bar;
  
  std::vector<A>* pbar =&bar; // This is what I have

  for (int i=1; i<5; i++)
    foo.push_back (i);
 
 
 // Is this legal?
  std::transform (foo.begin(), foo.end(), std::back_inserter(*pbar), some_function);
                                                  // bar: 2 4 6 8 10

  std::cout << "foo contains:";
  for (std::vector<int>::iterator it=foo.begin(); it!=foo.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';
  
   std::cout << "bar contains:";
  for (std::vector<A>::iterator it=bar.begin(); it!=bar.end(); ++it)
    std::cout << ' ' << it->GetValue();
  std::cout << '\n';

  return 0;
}
