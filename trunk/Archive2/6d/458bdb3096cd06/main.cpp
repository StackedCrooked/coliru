#include <iostream>

int main()
{
    int x;
	while(std::cin >> x)
	{
		switch(x)
		{
			case 1 ... 100: std::cout << "a"; break;
			default: std::cout << "b"; break;
		}
	}
}
