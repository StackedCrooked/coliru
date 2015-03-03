#include <iostream>
#include <bitset>
#include <ctime>
using namespace std;

int main()
{
	uint64_t start, finish;
	int a;
	bitset<8> b1;
	b1[0] = 0;
	char b2 = 0;

	start = clock();
	for( a = 0; a < 1000000; a++ )
	{
		if(b1[0]) break;
	}
	finish = clock();
    auto t1 = finish - start / double(CLOCKS_PER_SEC);
    
	start = clock();
	for( a = 0; a < 1000000; a++ )
	{
		if(b2 & (1<<0)) break;
	}
    finish = clock();
    auto t2 = finish - start / double(CLOCKS_PER_SEC);
	cout << "times:" << t1 << "/" << t2 << " ration:" << t1 / t2 << endl;
}