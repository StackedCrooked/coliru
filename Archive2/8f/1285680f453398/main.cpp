#include <iostream>

using namespace std;

int main()
{
    // 1:
	int m = [](int x)
	{
		return [](int y)
			{
				return y*2;
			}(x)+3;
	}(5);
	cout<<m<<endl;

	// 2:
	auto ff=[](int x,int y)
	{
		return x+y;
	}(4,5);
	cout<<ff(21,12)<<endl;
}