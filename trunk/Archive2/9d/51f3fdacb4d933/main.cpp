#include <iostream>
using namespace std;

using namespace std;

struct T 
{ 
    T() : i(0) {} 
	void inc() { i++; } 
	int i; 
}; 

T modify(T &t) 
{ 
	t.inc(); return t; 
} 

int main()
{
	modify(modify(T()));
	return 0;
}
