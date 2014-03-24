#include <cstdlib>
#include <iostream>

int simpleMemLeak()
{
    //dynamic memory allocation
	int* pint = new int;

	//assign value by dereference
	*pint = 10;

	//return value by dereference
	//allocated memory is lost in every function call
	return *pint;
}

int main() {
	//it will cause bad_alloc exception because of memory leaks
	for (int i = 0; i < 100000; i++)
		simpleMemLeak();
}