#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <array>
#include <iostream>

using namespace std;

int main()
{
    const int items = 500000;

	clock_t begin_time = clock();
	
	int data[items];

	for(int i = 0; i < items; i++)
		data[i] = 100;

	std::cout << "C array took: " << float( clock () - begin_time ) /  CLOCKS_PER_SEC << endl;
	
	begin_time = clock();

	std::array<int, items> a;
	
	for(int i = 0; i < items; i++)
		a[i] = 100;

	std::cout << "C++ array took: " << float( clock () - begin_time ) /  CLOCKS_PER_SEC << endl;

	cin.get();

	for(int i = 0; i < items; i++)
		cout << data[i] << " " << a[i];

	return 0;
}