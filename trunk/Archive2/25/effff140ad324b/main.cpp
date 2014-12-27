#include <thread> 
#include <iostream>

int funk_a(int (*d)[10][10])
{
    std::cout << (*d)[0][1] << std::endl;
    return 0;
}

int main()
{
	int devays[10][10] = { {1,2,3} };
	std::thread t(funk_a, &devays);
	t.join();
}