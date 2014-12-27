#include <thread> 
#include <iostream>

int funk_2(int (*d)[10][10])
{
    std::cout << (*d)[0][2] << std::endl;
    return 0;
}

int funk_a(int (*d)[10][10])
{
    std::cout << (*d)[0][1] << std::endl;
    std::thread t(funk_2, d);
    t.join();    
    return 0;
}

int main()
{
	int devays[10][10] = { {1,2,3} };
	std::thread t(funk_a, &devays);
	t.join();
}