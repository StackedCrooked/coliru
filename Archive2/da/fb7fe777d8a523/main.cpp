#include <vector>
#include <cmath>

#include <iostream>

size_t x = 3.14;
 
template <class T>
void dosomething(int v[], T idx)
{
    v[std::abs(idx)] = 1;
}

int main()
{ 
	int v [10];
    unsigned u = 0;
    
    dosomething(v, u);
    
	std::cout << x;
}
