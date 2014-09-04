#include <vector>


class A
{
 
 A& operator= (const A& rhs);
 public:
 int d;
 };



 int main()
 {
  std::vector<A> v;
  A a;
  v.push_back(a);
 
 }

