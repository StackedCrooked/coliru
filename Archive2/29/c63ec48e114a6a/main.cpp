#include <iostream>
#include <list>

struct item { int b; };
using lst = std::list<item>;

int main()
{
	const lst values = {{2}, {3}, {4}, {5}, {6}, {7}};
    lst::const_iterator iter = values.begin();
    iter->b++;
    
    return 0;
}