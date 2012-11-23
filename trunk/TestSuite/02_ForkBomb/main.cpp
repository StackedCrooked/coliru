#if 0
g++ -o test main.cpp && ./test
#endif

#include <unistd.h>

int main()
{
	while (true) fork();
}
