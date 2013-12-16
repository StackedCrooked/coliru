#include <algorithm>
#include <cmath>
#include <cstring>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <initializer_list>
#include <ostream>
#include <stdexcept>
#include <vector>


using namespace std;

void f(int n)
{
    static int s = n;

	printf("s = %d\tn = %d\n",s,n);

	s = n;
}

int main()
{
	f(1);
	f(2);
	f(3);
}
