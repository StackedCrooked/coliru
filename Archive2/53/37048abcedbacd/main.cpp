#include <boost/multi_array.hpp>
#include <iostream>

using namespace std;
using namespace boost;

int main()
{
	multi_array<double, 2> m(extents[2][3]);
    
    m[1][1] = 5;
    
    cout << m[1][1];
}
