#include <iostream>
#include <bitset>
using namespace std;

__attribute__((noinline)) uint64_t processorTicks()
{
    uint64_t tt;
    asm volatile (
        "rdtsc;"
        "shrd $32, %%rdx, %%rax;"
        :"=a"(tt)
        :
        :"%rdx"
    );
    return tt;
}

int main()
{
	uint64_t start, finish;
	int a;
	bitset<8> b1;
	b1[0] = 0;
	char b2 = 0;

	start = processorTicks();
	for( a = 0; a < 1000000; a++ )
	{
		if(b1[0]) break;
	}
	finish = processorTicks();
    auto t1 = finish - start;
    
	start = processorTicks();
	for( a = 0; a < 1000000; a++ )
	{
		if(b2 & (1<<0)) break;
	}
    finish = processorTicks();
    auto t2 = finish - start;
	cout << "times:" << t1 << "/" << t2 << " ration:" << double(t1) / t2 << endl;
}