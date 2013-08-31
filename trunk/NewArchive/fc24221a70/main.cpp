#include <stdio.h>
#include <assert.h>
 
int main ()
{
	// Test if 0 is really equivalent to 0
	assert (0 == 0);
 
	// Test if 1 is different than 0...
	assert (1 == 0);
 
	return 0;
}