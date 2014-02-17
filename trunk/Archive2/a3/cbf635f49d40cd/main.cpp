#include <iostream>
#include <string>
#include <vector>

class foo
{
public:
    foo() 
	{
		std::cout << "Regular Contstructor" << "\n";
	}

	foo(const foo& that)
	{
		std::cout << "Copy Contstructor" << "\n";
	}

	foo& operator=(const foo& that)
	{
		std::cout << "Assignment copy operator" << "\n";
		return *this;
	}

	foo(foo&& that)
	{
		
		std::cout << "Move Contstructor" << "\n";
	}

	foo& operator=(foo&& that) //Rvalue
	{
		//b= std::move(a);
		std::cout << "Assignment Move copy operator" << "\n";
		return *this;
	}

};

foo myfunction()
{
	foo b;
	return b;
}

int main()
{
	foo b = foo();      
	std::cin.get();
    return 0;
}
