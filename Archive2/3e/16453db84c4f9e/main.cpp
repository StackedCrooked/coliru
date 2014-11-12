#include <string>
#include <sstream>
#include <iostream>

using std::string;
using std::stringstream;
using std::cout;

int sorpmaxker(string _sor)
{
    int num;
    int maxi;
    int i = 0;
	stringstream ss(_sor);
	ss >> num;

    while (ss >> num)
	{
        cout << "i = " << i << std::endl;

		if (i == 0)
		{
			maxi = num;
			i++;
		}
		if (num>maxi && num % 2 == 0)
		{
			maxi = num;
		}
		ss >> num;
	}
	if (i==0)
	{
		return 1;
	} else return maxi;
}

int main()
{
    std::cout << sorpmaxker("1 2 3 4 5 6 7 8 9 10") << std::endl;
}
