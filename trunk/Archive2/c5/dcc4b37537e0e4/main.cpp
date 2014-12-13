#include <iostream>
using namespace std;

class Base
{
public:
    Base()
	{
		cout << "empty\n";
	}
    Base(int n)
    {
		cout << "int\n";
	}
	/*template <typename T>
	Base(std::initializer_list<T>)
	{
		cout << "list\n";
	}*/
};

int main() {
	Base b = {1};
	// your code goes here
	return 0;
}