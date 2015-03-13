
#include <iostream>

int* copyToArray(int (&a)[2]) {
    a[0] = 5;
	a[1] = 6;

	return a;
}

int main()
{
    int asdf[2] = {};
    copyToArray(asdf);
   
    return asdf[0];
}