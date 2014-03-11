#include <boost/lockfree/queue.hpp>
#include <iostream>

using namespace boost::lockfree;

struct X { int i; std::string s; };

int main()
{
    queue<int, capacity<50> > q;
}
