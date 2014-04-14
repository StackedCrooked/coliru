#include <deque>
#include <iostream>

#include "boost/shared_ptr.hpp"


struct Widget
{
  boost::shared_ptr<int> p;

  Widget() : p(new int(42)) {}
};


int main()
{
  std::deque<Widget> d(10);
  for (size_t i = 0; i < d.size(); ++i)
    std::cout << "d[" << i << "] : " << d[i].p.use_count() << '\n';
}
