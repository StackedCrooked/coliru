#include <cstdlib>
#include <cstdio>
#include <vector>

using namespace std;


void push_test()
{
	std::vector<int> vec;

    printf("vec.size()=%lu  vec.capacity()=%lu\n", (unsigned long)vec.size(), (unsigned long)vec.capacity());

    for (int i = 0; i < 20; ++i) {
        vec.push_back(i);
	    printf("vec.push_back(%2d) -> vec.size()=%2lu  vec.capacity()=%2lu\n", i, (unsigned long)vec.size(), (unsigned long)vec.capacity());
    }
}


int main()
{
	push_test();
	
	return EXIT_SUCCESS;
}
