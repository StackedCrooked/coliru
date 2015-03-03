#include <iostream>
#include <bitset>
#include <ctime>

int main()
{
    clock_t start, finish;
	unsigned a;
	std::bitset<8> b1;
	b1[0] = 0;
	char b2 = 0;
	start = clock();
    
    start = clock();
	for( a = 0; a < 10000000; ++a )
	{
		b2 ^= (1 << (a % 8)); //Actual work done, hamper too smart optimisation
	}
    finish = clock();
    double t1 = (finish - start) / double(CLOCKS_PER_SEC);
    
    start = clock();
	for( a = 0; a < 10000000; ++a )
	{
		b1.flip(a % 8); //Actual work done, hamper too smart optimisation
	}
	finish = clock();
    double t2 = (finish - start) / double(CLOCKS_PER_SEC);


	std::cout << "times:" << t1 << "/" << t2 << " ration:" << t1 / t2 << '\n';
	std::cout << b1 << b2; //Need to disable too smart optimisation
}
