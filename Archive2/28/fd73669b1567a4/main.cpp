#include <iostream>
#include <string>
#include <set>
 
// Helper function for printing pairs.
template<class Ch, class Tr, class A, class B> inline
std::basic_ostream<Ch, Tr>& operator<<(std::basic_ostream<Ch, Tr>& stream, std::pair<A,B> p)
{
  return stream << '(' << p.first << ", " << p.second << ')';
}
 
// Helper function for printing containers.
template<class Ch, class Tr, class Co>
std::basic_ostream<Ch, Tr>& operator<<(std::basic_ostream<Ch, Tr>& stream, Co& c)
{
  stream << '{' << *c.begin();
 
  for(auto it = ++(c.begin()); it != c.end(); ++it)
    stream << ", " << *it;
 
  stream << '}' << std::endl;
  return stream;
}
 
int main()
{
  // (1) Default constructor
  std::set<std::string> a;
  a.insert("something");
  a.insert("anything");
  a.insert("that thing");
  std::cout << "a = " << a;
 
  // (2) Iterator constructor
  std::set<std::string> b(a.find("anything"), a.end());
  std::cout << std::string(80, '-') << std::endl;
  std::cout << "b = " << b;
 
  // (3) Copy constructor
  std::set<std::string> c(a);
  c.insert("another thing");
  std::cout << std::string(80, '-') << std::endl;
  std::cout << "a = " << a;
  std::cout << "c = " << c;
 
  // (4) Move constructor
  std::set<std::string> d(std::move(a));
  std::cout << std::string(80, '-') << std::endl;
  std::cout << "a = nullptr" << std::endl;
  std::cout << "d = " << d;
 
  // (5) Initializer list constructor
  std::set<std::string> e{
    "one", "two", "three", "five", "eight"
  };
  std::cout << std::string(80, '-') << std::endl;
  std::cout << "e = " << e;
}