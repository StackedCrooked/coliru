//started 3:35AM
#include <iostream>
#include <string>

int main() {
    std::string a(30,'0'), b(30,'0');

	while(std::getline(std::cin, a))
	{
		int c = 0;
		for(int i = 29; i >= 0; --i)
		{
			int n = (a[i] + b[i] - '0') + c;
			if(n > '9')
			{
				n -= 10;
				c = 1;
			}
			else c = 0;
			
			b[i] = n;
		}
	}
	std::cout << b;
}