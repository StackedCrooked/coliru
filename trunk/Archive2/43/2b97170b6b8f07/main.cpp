#include <iostream>
#include <map>

/**
 * A comparator that defines strict-weak ordering,
 * but is backwards!
 */
struct Comp
{
   bool operator()(const int& lhs, const int& rhs)
   { return rhs < lhs; }
};

int main()
{
   {
      std::map<int, char> m;        // uses default less<int> comparator
      m[0] = 'a';
      m[1] = 'b';
      m[2] = 'c';
      
      for (auto el : m)
         std::cout << el.second;    // "abc"
   }
   {
      std::map<int, char, Comp> m;  // uses my own comparator defined above
      m[0] = 'a';
      m[1] = 'b';
      m[2] = 'c';
      
      for (auto el : m)
         std::cout << el.second;    // "cba"  ... which is true ;)
   }
}