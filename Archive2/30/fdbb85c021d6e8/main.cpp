#include <iostream>       
#include <thread>
#include <functional>


void foo(int& x)
{
    std::cout << x << std::endl;
}


int main()
{
	int value = 10;
	foo(value);

	std::thread th(foo, value);

	th.join();
}
