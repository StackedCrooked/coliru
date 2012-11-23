#if 0
g++ -o test main.cpp && ./test && exit
#endif

#include <cstdlib>

int main()
{
	system("find / | xargs cat");
}
