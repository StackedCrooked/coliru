#include <boost/range/irange.hpp>
#include <iostream>
#include <string>

using namespace boost;
using namespace std;

int main()
{
  for(auto i : irange(1, 11))
      cout << string(i,'*') << string(11-i,' ') <<
              string(11-i,'*') << string((2*i),' ') << 
              string(11-i,'*') << string(11-i,' ') <<
              string(i,'*') << endl;
}
