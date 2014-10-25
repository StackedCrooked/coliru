#include <iostream>
#include <map>
#include <set>
#include <stack>

int main()
{
  typedef std::uint64_t num;

  // ys[x] is the length of the chain starting at x.
  // xms is the set of numbers that yield the longest chains.
  // ym is the length of the longest chain so far.
  std::map<num, num> ys = {{1,1}};
  std::set<num> xms = {1};
  num ym = 1;

  for (num i = 2; i < 1000000; ++i)
  {
    std::stack<num> xs;
    num x = i, y = ys[x];

    // Compute successive chain elements until
    // a base element is reached whose chain
    // length has already been memoized.
    while (!y)
    {
      xs.push(x);
      x = (x & 1) ? (3*x + 1) : (x/2);
      y = ys[x];
    }

    // The lengths of the newly computed elements
    // can be found by repeatedly incrementing
    // the base element's chain length.
    while (!xs.empty())
    {
      x = xs.top();
      ys[x] = ++y;
      xs.pop();
    }

    // Keep track of which number(s)
    // yield the longest chain(s).
    if (y >= ym)
    {
      if (y > ym)
      {
        xms.clear();
        ym = y;
      }
      xms.insert(x);
    }
  }

  for (num xm : xms)
    std::cout << xm << ' ';

  return 0;
}