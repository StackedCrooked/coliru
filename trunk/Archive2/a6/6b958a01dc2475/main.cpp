#include <iostream>

void f()
{
}
int g(...)
{
    return 0;
}

int main()
{
	int x = g(f());
	std::cout << "x = " << x << std::endl;
}
