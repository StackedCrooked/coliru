
#include <functional>
#include <iostream>

typedef std::function< int()> fntype;

void foo(const fntype& fn)
{
    try
	{
		if(fn)
			fn();
		else
			std::cout << "fn is empty" << std::endl;
	}
	catch(const std::bad_function_call&)
	{
		std::cout << "fn threw anyways" << std::endl;
	}
}


int main(int argc, char **argv)
{
	// OK
	std::function<int()> nothing;
	foo(nothing);

	// Fails
	std::function<const int()> nothing2;
	foo(nothing2);
    
	return 0;
}
